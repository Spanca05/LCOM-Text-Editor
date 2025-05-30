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
#include "graphics/font16x32.h"
#include "graphics/text_renderer.h"

static uint8_t kbd_bit;
// static uint8_t timer_bit;  // no longer using timer for auto-repeat
// static void   *video_mem   = NULL;
static void   *back_buffer = NULL;

static TextBuffer tb; // persistent text buffer

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

    // Initial render so the screen is shown before any keypress
    render_screen();

    bool    running = true;
    int     ipc_status;
    message msg;

    // Main event loop
    while (running) {
        if (driver_receive(ANY, &msg, &ipc_status) != OK) continue;
        if (is_ipc_notify(ipc_status) && _ENDPOINT_P(msg.m_source) == HARDWARE) {
            uint32_t irq_set = msg.m_notify.interrupts;

            // Keyboard interrupt: handle key make codes only
            if (irq_set & kbd_bit) {
                uint16_t scancode;
                if (keyboard_ih(&scancode) != RES_OK) continue;
                uint8_t code     = scancode & 0x7F;
                bool    is_break = scancode & 0x0080;

                if (is_break)              // ignore key releases
                    continue;

                if (code == 0x01) {        // ESC make code
                    running = false;
                } else if (code == 0x0E) { // Backspace make code
                    text_buffer_delete_char(&tb);
                } else {                   // Other printable key make
                    text_buffer_insert_char(&tb, (char)code);
                }
            }
        }
        render_screen();
    }

    // Cleanup and restore text mode
    cleanup();
    return RES_OK;
}

// Render the window header (title bar)
static void render_header(void *buf, uint16_t header_height) {
    uint32_t header_bg = 0x333333;
    // Background
    res_vg_draw_rectangle(buf, 0, 0, mode_info.XResolution, header_height, header_bg);
    // Text "File" on left, 'X' on right
    uint16_t text_y = (header_height - FONT_HEIGHT) / 2;
    draw_string(buf, 5, text_y, "File", 0xFFFFFF);
    draw_char(buf, mode_info.XResolution - FONT_WIDTH - 5, text_y, 23, 0xFF0000);
}

// Render the window footer
static void render_footer(void *buf, uint16_t header_height) {
    uint32_t footer_bg = 0x333333;
    uint16_t y0        = mode_info.YResolution - header_height;
    res_vg_draw_rectangle(buf, 0, y0, mode_info.XResolution, header_height, footer_bg);

    // Draw cursor position (Ln, Col) on the left side
    char pos_text[32];
    snprintf(pos_text, sizeof(pos_text), "Ln %u, Col %u", tb.cursor_row + 1, tb.cursor_col + 1);
    uint16_t text_y = y0 + (header_height - FONT_HEIGHT) / 2;
    draw_string(buf, 5, text_y, pos_text, 0xFFFFFF);
}

void render_screen() {
    // Clear screen to grey
    res_vg_draw_rectangle(back_buffer, 0, 0, mode_info.XResolution, mode_info.YResolution, 0xCCCCCC);

    // Header and footer heights
    uint16_t header_height = FONT_HEIGHT + 4;

    // Draw header and footer
    render_header(back_buffer, header_height);
    render_footer(back_buffer, header_height);

    // Draw text buffer contents below header
    text_buffer_render(&tb, back_buffer, header_height);

    // TODO: draw cursor here

    // Swap buffers
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
