/**
 * @file text_buffer.c
 * @brief Implementation of text buffer management functions.
 */

#include "text_buffer.h"
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
    if (tb->cursor_col >= MAX_COLS) {
        tb->cursor_col = 0;
        tb->cursor_row = (tb->cursor_row + 1) % MAX_ROWS;
    }
    return RES_OK;
}

Result(text_buffer_delete_char)(TextBuffer *tb) {
    if (tb == NULL) return RES_INVALID_ARGUMENT;

    // If at start of buffer, nothing to delete
    if (tb->cursor_row == 0 && tb->cursor_col == 0) return RES_OK;

    // Determine deletion position and update cursor
    uint16_t del_row = tb->cursor_row;
    uint16_t del_col;
    if (tb->cursor_col > 0) {
        del_col = tb->cursor_col - 1;
    } else {
        // At start of line: wrap to previous line
        del_row = tb->cursor_row - 1;
        del_col = MAX_COLS - 1;
    }
    tb->cursor_row = del_row;
    tb->cursor_col = del_col;

    // Shift characters left in the line to fill the gap
    size_t move_count = (MAX_COLS - del_col - 1) * sizeof(char);
    memmove(&tb->buffer[del_row][del_col], &tb->buffer[del_row][del_col + 1], move_count);
    tb->buffer[del_row][MAX_COLS - 1] = ' ';

    return RES_OK;
}

Result(text_buffer_move_cursor)(TextBuffer *tb, uint16_t row, uint16_t col) {
    if (tb == NULL) return RES_INVALID_ARGUMENT;
    if (row >= MAX_ROWS || col >= MAX_COLS) return RES_INVALID_ARGUMENT;

    tb->cursor_row = row;
    tb->cursor_col = col;
    return RES_OK;
}

Result(text_buffer_render)(const TextBuffer *tb, void *buf) {
    if (tb == NULL || buf == NULL) return RES_INVALID_ARGUMENT;

    // Draw each character in the buffer
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            draw_char(buf, col * FONT_WIDTH, row * FONT_HEIGHT, tb->buffer[row][col], 0xFFFFFF);
        }
    }
    return RES_OK;
}
