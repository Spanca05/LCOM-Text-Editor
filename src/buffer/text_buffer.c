/**
 * @file text_buffer.c
 * @brief Implementation of text buffer management functions.
 */

#include "text_buffer.h"
#include "../drivers/graphics.h" // for mode_info
#include "../graphics/font8x16.h"
#include "../graphics/text_renderer.h"
#include "../utils/result.h"
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

Result(text_buffer_init)(TextBuffer *tb) {
    if (tb == NULL) return RES_INVALID_ARGUMENT;

    // Clear the buffer and reset cursor
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) { tb->buffer[row][col] = ' '; }
    }
    tb->cursor_row = 0;
    tb->cursor_col = 0;

    return RES_OK;
}

Result(text_buffer_insert_char)(TextBuffer *tb, char c) {
    if (tb == NULL) return RES_INVALID_ARGUMENT;

    // Place character at current cursor position
    tb->buffer[tb->cursor_row][tb->cursor_col] = c;
    // Advance cursor
    tb->cursor_col++;
    // Wrap to next line based on dynamic screen width
    uint16_t max_cols = mode_info.XResolution / FONT_WIDTH;
    if (tb->cursor_col >= max_cols) {
        tb->cursor_col = 0;
        tb->cursor_row = (tb->cursor_row + 1) % (mode_info.YResolution / FONT_HEIGHT);
    }
    return RES_OK;
}

Result(text_buffer_delete_char)(TextBuffer *tb) {
    if (tb == NULL) return RES_INVALID_ARGUMENT;

    // If at very start, nothing to delete
    if (tb->cursor_row == 0 && tb->cursor_col == 0) return RES_OK;

    // Compute dynamic dimensions
    uint16_t max_cols = mode_info.XResolution / FONT_WIDTH;

    // Move cursor back one position
    if (tb->cursor_col > 0) {
        tb->cursor_col--;
    } else if (tb->cursor_row > 0) {
        tb->cursor_row--;
        tb->cursor_col = max_cols - 1;
    }

    // Now delete at this new cursor position by shifting rest of line
    uint16_t r   = tb->cursor_row;
    uint16_t c   = tb->cursor_col;
    size_t   cnt = (max_cols - 1 - c) * sizeof(char);
    memmove(&tb->buffer[r][c], &tb->buffer[r][c + 1], cnt);
    tb->buffer[r][max_cols - 1] = ' ';

    return RES_OK;
}

Result(text_buffer_move_cursor)(TextBuffer *tb, uint16_t row, uint16_t col) {
    if (tb == NULL) return RES_INVALID_ARGUMENT;
    if (row >= MAX_ROWS || col >= MAX_COLS) return RES_INVALID_ARGUMENT;

    tb->cursor_row = row;
    tb->cursor_col = col;
    return RES_OK;
}

Result(text_buffer_render)(const TextBuffer *tb, void *buf, uint16_t y_offset) {
    if (tb == NULL || buf == NULL) return RES_INVALID_ARGUMENT;

    // Compute available drawing area between header and footer
    uint16_t total_height     = mode_info.YResolution;
    uint16_t available_pixels = (total_height > 2 * y_offset) ? (total_height - 2 * y_offset) : 0;
    uint16_t max_rows_draw    = available_pixels / FONT_HEIGHT;

    // Draw each character in the buffer within the drawing area
    for (uint16_t row = 0; row < MAX_ROWS && row < max_rows_draw; row++) {
        for (uint16_t col = 0; col < MAX_COLS; col++) {
            uint16_t x = col * FONT_WIDTH;
            uint16_t y = y_offset + row * FONT_HEIGHT;
            draw_char(buf, x, y, tb->buffer[row][col], 0xFFFFFF);
        }
    }
    return RES_OK;
}
