#include <lcom/lcf.h>
#include <lcom/video_gr.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "buffer/text_buffer.h"
#include "drivers/VBE.h"
#include "drivers/backbuffer.h"
#include "drivers/graphics.h"
#include "drivers/i8042.h"
#include "drivers/i8254.h"
#include "drivers/keyboard.h"
#include "drivers/timer.h"
#include "graphics/text_renderer.h"

static uint8_t kbd_bit;
static uint8_t timer_bit;
static void   *video_mem   = NULL;
static void   *back_buffer = NULL;

static TextBuffer tb;  // persistent text buffer

bool handle_keyboard(uint16_t scancode);
void render_screen(void);
void test_text_buffer(void);

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
    if (set_graphic_mode(VBE_864P_DC) != RES_OK) {
        fprintf(stderr, "Failed to set graphics mode\n");
        cleanup();
        exit(EXIT_FAILURE);
    }

    if (res_vg_init(VBE_864P_DC, &video_mem) != RES_OK) {
        fprintf(stderr, "Failed to map video memory\n");
        cleanup();
        exit(EXIT_FAILURE);
    }

    // Initialize back buffer
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

    // Initialize text buffer
    if (text_buffer_init(&tb) != RES_OK) {
        fprintf(stderr, "Failed to init text buffer\n");
        cleanup();
        return EXIT_FAILURE;
    }

    bool running = true;
    int ipc_status;
    message msg;

    // Main event loop
    while (running) {
        if (driver_receive(ANY, &msg, &ipc_status) != OK) continue;
        if (is_ipc_notify(ipc_status) && _ENDPOINT_P(msg.m_source) == HARDWARE) {
            uint32_t irq_set = msg.m_notify.interrupts;

            if (irq_set & timer_bit) {
                // Timer interrupt: toggle cursor blink flag (optional)
            }

            if (irq_set & kbd_bit) {
                uint16_t scancode;
                keyboard_ih(&scancode);
                if (scancode == BREAK_ESC) {
                    running = false;
                } else {
                    // insert character into buffer or handle arrows
                    // TODO Add scancode to char logic
                    text_buffer_insert_char(&tb, (char)scancode);
                }
            }
        }
        render_screen();
    }

    // Cleanup and restore text mode
    cleanup();
    return RES_OK;
}

void render_screen() {
    // Clear screen to grey in back buffer
    res_vg_draw_rectangle(back_buffer, 0, 0, mode_info.XResolution, mode_info.YResolution, 0xCCCCCC);

    // draw text buffer contents
    text_buffer_render(&tb, back_buffer);

    // Draw some text
    draw_string(back_buffer, 50, 50, "Press ESC to exit", 0xFFFFFF);
    draw_char(back_buffer, 50, 70, 'P', 0x00FF00);

    // TODO: draw cursor here

    // Copy back buffer to video memory
    swap_buffers(back_buffer);
}

void test_text_buffer() {
    TextBuffer tb;

    // Initialize the text buffer
    if (text_buffer_init(&tb) != RES_OK) {
        printf("Failed to initialize text buffer\n");
        return;
    }

    // Insert a character at (0, 0)
    text_buffer_insert_char(&tb, 'A');
    printf("Buffer after inserting 'A' at (0, 0):\n");
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) { putchar(tb.buffer[row][col]); }
        putchar('\n');
    }

    // Move the cursor to (5, 10)
    if (text_buffer_move_cursor(&tb, 5, 10) != RES_OK) {
        printf("Failed to move cursor\n");
        return;
    }
    printf("Cursor moved to row %d, col %d\n", tb.cursor_row, tb.cursor_col);
}
