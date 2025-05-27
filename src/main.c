#include <lcom/lcf.h>
#include <lcom/video_gr.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "drivers/VBE.h"
#include "drivers/graphics.h"
#include "drivers/i8042.h"
#include "drivers/i8254.h"
#include "drivers/keyboard.h"
#include "drivers/timer.h"

static uint8_t kbd_bit;
static uint8_t timer_bit;
static void   *video_mem = NULL;

bool handle_keyboard(uint16_t scancode);
void render_screen();

int main(int argc, char *argv[]) {
    // Initialize LCF and Minix framework
    lcf_set_language("EN-US");
    if (lcf_start(argc, argv)) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void cleanup() {
    res_timer_unsubscribe_int();
    keyboard_unsubscribe_int();
    if (set_text_mode() != RES_OK) fprintf(stderr, "Failed to restore text mode\n");
}

void setup_graphics() {
    // Set graphics mode and map video memory
    if (set_graphic_mode(VBE_1024P_DC) != RES_OK) {
        fprintf(stderr, "Failed to set graphics mode\n");
        cleanup();
        exit(EXIT_FAILURE);
    }

    if (res_vg_init(VBE_1024P_DC, &video_mem) != RES_OK) {
        fprintf(stderr, "Failed to map video memory\n");
        cleanup();
        exit(EXIT_FAILURE);
    }
}

void subscribe_to_devices() {
    // Subscribe timer interrupts
    if (res_timer_subscribe_int(&timer_bit) != RES_OK) {
        fprintf(stderr, "Failed to subscribe timer\n");
        cleanup();
        exit(EXIT_FAILURE);
    }

    // Subscribe keyboard interrupts
    if (keyboard_subscribe_int(&kbd_bit) != RES_OK) {
        fprintf(stderr, "Failed to subscribe keyboard\n");
        cleanup();
        exit(EXIT_FAILURE);
    }
}

int(proj_main_loop)(int argc, char *argv[]) {
    setup_graphics();
    subscribe_to_devices();

    bool    running = true;
    int     ipc_status;
    message msg;

    // Main event loop
    while (running) {
        if (driver_receive(ANY, &msg, &ipc_status) != OK) continue;
        if (is_ipc_notify(ipc_status) && _ENDPOINT_P(msg.m_source) == HARDWARE) {
            uint32_t irq_set = msg.m_notify.interrupts;

            if (irq_set & BIT(timer_bit)) {}

            if (irq_set & BIT(kbd_bit)) {
                uint16_t scancode;
                keyboard_ih(&scancode);
                printf("%d", scancode);
                if (scancode == BREAK_ESC) running = false;
            }
        }

        render_screen();
    }

    // Cleanup and restore text mode
    cleanup();
    return RES_OK;
}

void render_screen() {
    // Clear screen to light grey
    res_vg_draw_rectangle(0, 0, mode_info.XResolution, mode_info.YResolution, 0xCCCCCC);
    // TODO: draw text buffer and cursor here using vg_draw_pixel or custom font routines
}
