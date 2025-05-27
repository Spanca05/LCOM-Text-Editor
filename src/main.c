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

#define GRAPHICS_MODE VBE_768P_INDEXED
#define TEXT_MODE     0x03

static uint8_t kbd_bit;
static int     kbd_hook = KEYBOARD_IRQ;
static uint8_t timer_bit;
static int     timer_hook = TIMER0_IRQ;
static void   *video_mem  = NULL;

extern uint16_t scancode; // from kbd.c

bool handle_keyboard(uint16_t scancode);
void render_screen();
void cleanup();

int main(int argc, char *argv[]) {
    // Initialize LCF and Minix framework
    lcf_set_language("EN-US");
    if (lcf_start(argc, argv)) return EXIT_FAILURE;

    // Cleanup and restore text mode
    cleanup();
    return EXIT_SUCCESS;
}

int(proj_main_loop)(int argc, char *argv[]) {
    // Set graphics mode and map video memory
    if (set_graphic_mode(GRAPHICS_MODE) != RES_OK) {
        fprintf(stderr, "Failed to set graphics mode\n");
        return EXIT_FAILURE;
    }

    if (res_vg_init(GRAPHICS_MODE, &video_mem) != RES_OK) {
        fprintf(stderr, "Failed to map video memory\n");
        return EXIT_FAILURE;
    }

    // Subscribe keyboard interrupts
    if (kbd_subscribe_int(&kbd_bit) != RES_OK) {
        fprintf(stderr, "Failed to subscribe keyboard\n");
        cleanup();
        return EXIT_FAILURE;
    }

    // Subscribe timer interrupts
    if (res_timer_subscribe_int(&timer_bit) != RES_OK) {
        fprintf(stderr, "Failed to subscribe timer\n");
        cleanup();
        return EXIT_FAILURE;
    }

    bool    running = true;
    int     ipc_status;
    message msg;

    // Main event loop
    while (running) {
        if (driver_receive(ANY, &msg, &ipc_status) != OK) continue;
        if (is_ipc_notify(ipc_status) && _ENDPOINT_P(msg.m_source) == HARDWARE) {
            uint32_t irq_set = msg.m_notify.interrupts;

            if (irq_set & BIT(kbd_hook)) {
                kbc_ih();
                running = handle_keyboard(scancode);
                render_screen();
            }
            if (irq_set & BIT(timer_hook)) {
                timer_int_handler();
                render_screen();
            }
        }
    }

    return RES_OK;
}

bool handle_keyboard(uint16_t scancode) {
    if (scancode == BREAK_ESC) // ESC pressed
        return false;
    // TODO: handle printable characters, backspace, arrow keys, etc.
    return true;
}

void render_screen() {
    // Clear screen to light grey
    res_vg_draw_rectangle(0, 0, mode_info.XResolution, mode_info.YResolution, 0xCCCCCC);
    // TODO: draw text buffer and cursor here using vg_draw_pixel or custom font routines
}

void cleanup() {
    timer_unsubscribe_int();
    kbd_unsubscribe_int();
    if (set_text_mode() != RES_OK) fprintf(stderr, "Failed to restore text mode\n");
}
