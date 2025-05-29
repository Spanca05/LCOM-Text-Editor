#ifndef TEXT_BUFFER_H
#define TEXT_BUFFER_H

#include "../utils/result.h"
#include <stdbool.h>
#include <stdint.h>

#define MAX_ROWS 25
#define MAX_COLS 80

/**
 * @brief Represents the text buffer and its state.
 */
typedef struct {
    char buffer[MAX_ROWS][MAX_COLS]; /**< 2D array to store text. */
    uint16_t cursor_row; /**< Current row position of the cursor. */
    uint16_t cursor_col; /**< Current column position of the cursor. */
} TextBuffer;

/**
 * @brief Initializes the text buffer.
 *
 * Clears the buffer and sets the cursor to the top-left corner.
 *
 * @param tb Pointer to the TextBuffer structure.
 */
Result(text_buffer_init)(TextBuffer *tb);

/**
 * @brief Updates the text buffer with a character.
 *
 * Inserts a character at the current cursor position and moves the cursor.
 *
 * @param tb Pointer to the TextBuffer structure.
 * @param c Character to insert.
 */
Result(text_buffer_insert_char)(TextBuffer *tb, char c);

/**
 * @brief Moves the cursor within the text buffer.
 *
 * Updates the cursor position based on user input.
 *
 * @param tb Pointer to the TextBuffer structure.
 * @param row New row position.
 * @param col New column position.
 */
Result(text_buffer_move_cursor)(TextBuffer *tb, uint16_t row, uint16_t col);

/**
 * @brief Renders the text buffer to the screen.
 *
 * Draws the contents of the text buffer using the text renderer.
 *
 * @param tb Pointer to the TextBuffer structure.
 * @param buf Pointer to the graphics buffer.
 */
Result(text_buffer_render)(const TextBuffer *tb, void *buf);


#endif
