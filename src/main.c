#include <lcom/lcf.h>
#include <lcom/video_gr.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "drivers/VBE.h"
#include "drivers/backbuffer.h"
#include "drivers/graphics.h"
#include "drivers/i8042.h"
#include "drivers/i8254.h"
#include "drivers/keyboard.h"
#include "drivers/timer.h"
#include "text/text_renderer.h"

static uint8_t kbd_bit;
static uint8_t timer_bit;
static void   *video_mem   = NULL;
static void   *back_buffer = NULL;

bool handle_keyboard(uint16_t scancode);
void render_screen();

int main(int argc, char *argv[]) {
    // Initialize LCF and Minix framework
    lcf_set_language("EN-US");
    if (lcf_start(argc, argv)) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void cleanup() {
    if (timer_bit) res_timer_unsubscribe_int();
    if (kbd_bit) keyboard_unsubscribe_int();
    if (back_buffer) free_backbuffer(back_buffer);
    if (set_text_mode() != RES_OK) fprintf(stderr, "Failed to restore text mode\n");
}

void setup_graphics() {
    // Set graphics mode
    if (set_graphic_mode(VBE_864P_DC) != RES_OK) {
        fprintf(stderr, "Failed to set graphics mode\n");
        cleanup();
        exit(EXIT_FAILURE);
    }

    // Initialize graphics mode and map video memory
    if (res_vg_init(VBE_864P_DC, &video_mem) != RES_OK) {
        fprintf(stderr, "Failed to map video memory\n");
        cleanup();
        exit(EXIT_FAILURE);
    }

    // Initialize backbuffer (requires framebuffer size from res_vg_init)
    if (init_backbuffer(&back_buffer) != RES_OK) {
        fprintf(stderr, "Failed to initialize back buffer\n");
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

            if (irq_set & timer_bit) {
                // Timer interrupt handling
            }

            if (irq_set & kbd_bit) {
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
    // Draw into backbuffer
    // Clear backbuffer to background color
    memset(back_buffer, 0xCC, mode_info.XResolution * mode_info.YResolution * ((mode_info.BitsPerPixel + 7) / 8));

    // Draw some text
    // Temporarily map graphics.c drawing to backbuffer
    // (swap video_mem pointer if supported) -- or draw directly to physical and then swap
    draw_string(back_buffer, 50, 50, "Press ESC to exit", 0xFFFFFF);
    draw_char(back_buffer, 50, 70, 'P', 0x00FF00);
    // Swap backbuffer to front
    swap_buffers(back_buffer);
}
