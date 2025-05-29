#include "text_buffer.h"
#include "../utils/result.h"
#include <stddef.h>
#include <stdlib.h>

Result(text_buffer_init)(TextBuffer *tb) {
    if (tb == NULL) return RES_INVALID_ARGUMENT;

    // Clear the buffer
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            tb->buffer[row][col] = ' '; // Fill with spaces
        }
    }

    return RES_OK;
}

Result(text_buffer_insert_char)(TextBuffer *tb, char c) {
    if (tb == NULL) return RES_INVALID_ARGUMENT;

    // TODO Fix to write on the desired position (where the cursor is)
    //  For now, insert at (0, 0)
    tb->buffer[0][0] = 0;

    return RES_OK;
}

Result(text_buffer_move_cursor)(TextBuffer *tb, uint16_t row, uint16_t col) {
    if (tb == NULL) return RES_INVALID_ARGUMENT;

    // Ensure the cursor stays within bounds
    if (row >= MAX_ROWS || col >= MAX_COLS) return RES_INVALID_ARGUMENT;

    tb->cursor_row = row;
    tb->cursor_col = col;

    return RES_OK;
}
