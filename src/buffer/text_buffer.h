/**
 * @file text_buffer.h
 * @brief Text buffer management for storing and editing text content.
 */

#ifndef TEXT_BUFFER_H
#define TEXT_BUFFER_H

#include "../utils/result.h"
#include <stdbool.h>
#include <stdint.h>

#define MAX_ROWS 54
#define MAX_COLS 160

/**
 * @brief Represents the text buffer and its state.
 *
 * Contains the character grid and the cursor position.
 */
typedef struct {
    char     buffer[MAX_ROWS][MAX_COLS]; /**< 2D array storing text characters. */
    uint16_t cursor_row;                 /**< Current cursor row position. */
    uint16_t cursor_col;                 /**< Current cursor column position. */
} TextBuffer;

/**
 * @brief Initializes the text buffer and resets the cursor.
 *
 * Clears the buffer by filling spaces and sets the cursor to (0,0).
 *
 * @param tb Pointer to the TextBuffer to initialize.
 * @return RES_OK on success, or an error code.
 */
Result(text_buffer_init)(TextBuffer *tb);

/**
 * @brief Inserts a character at the current cursor position.
 *
 * Writes the character into the buffer, then advances the cursor,
 * wrapping to the next line if needed.
 *
 * @param tb Pointer to the TextBuffer.
 * @param c Character to insert.
 * @return RES_OK on success, or an error code.
 */
Result(text_buffer_insert_char)(TextBuffer *tb, char c);

/**
 * @brief Deletes the character to the left of the cursor.
 *
 * Moves the cursor back one position, shifts the remainder of the line left,
 * and fills the vacated space with a space character.
 *
 * @param tb Pointer to the TextBuffer.
 * @return RES_OK on success, or an error code.
 */
Result(text_buffer_delete_char)(TextBuffer *tb);

/**
 * @brief Moves the cursor to a specified location.
 *
 * Updates the cursor_row and cursor_col fields, ensuring they stay in bounds.
 *
 * @param tb Pointer to the TextBuffer.
 * @param row Target row (0-based).
 * @param col Target column (0-based).
 * @return RES_OK on success, or an error code if out of bounds.
 */
Result(text_buffer_move_cursor)(TextBuffer *tb, uint16_t row, uint16_t col);

/**
 * @brief Renders the contents of the text buffer to the screen at a vertical offset.
 *
 * Draws each character at its appropriate screen position using draw_char,
 * starting at pixel y = y_offset, and stops before the footer area.
 *
 * @param tb Pointer to the TextBuffer.
 * @param buf Graphics buffer (back buffer) pointer.
 * @param y_offset Vertical pixel offset to start drawing.
 * @return RES_OK on success, or an error code.
 */
Result(text_buffer_render)(const TextBuffer *tb, uint16_t y_offset);

#endif // TEXT_BUFFER_H
