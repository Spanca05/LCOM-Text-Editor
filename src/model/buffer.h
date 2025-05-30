#ifndef BUFFER_H
#define BUFFER_H

#include "character.h"
#include "cursor.h"
#include "line.h"

#define BUFFER_SEGMENT_SIZE 5

typedef struct Buffer {
    Cursor cursor;
    Line  *lines;
    size_t capacity;
    size_t length;
} Buffer;

extern Buffer text_buffer;

/**
 * Initializes the buffer, including the cursor and the first line.
 */
Result init_buffer();

/**
 * Increases the buffer's capacity by a predefined segment size.
 *
 * @return Result indicating success or memory error.
 */
Result increase_buffer_size();

/**
 * Checks if the buffer needs more capacity and increases it if necessary.
 *
 * @return Result indicating success or memory error.
 */
Result increase_buffer_size_if_necessary();

/**
 * Adds a new line at the specified position in the buffer.
 *
 * @param position The position where the new line should be added.
 * @return Result indicating success, invalid argument, or memory error.
 */
Result add_line_at(uint64_t position);

/**
 * Removes a line at the specified position in the buffer.
 *
 * @param position The position of the line to be removed.
 * @return Result indicating success or invalid argument.
 */
Result remove_line_at(uint64_t position);

/**
 * Updates the cursor's state based on a clock tick.
 */
void buffer_clock_tick();

/**
 * Moves the cursor up by one line. If the cursor is already on the first line,
 * it will remain there.
 *
 * @return Result indicating success.
 */
Result move_cursor_up();

/**
 * Moves the cursor down by one line. If the cursor is already on the last line,
 * it will remain there.
 *
 * @return Result indicating success.
 */
Result move_cursor_down();

/**
 * Moves the cursor left by one character. If the cursor is at the start of a line,
 * it moves to the end of the previous line. If already at the start of the buffer,
 * it does nothing.
 *
 * @return Result indicating success or does not exist if at the start of the buffer.
 */
Result move_cursor_left();

/**
 * Moves the cursor right by one character. If the cursor is at the end of a line,
 * it moves to the start of the next line. If already at the end of the buffer,
 * it does nothing.
 *
 * @return Result indicating success or does not exist if at the end of the buffer.
 */
Result move_cursor_right();

/**
 * Adds a character to the buffer at the current cursor position.
 *
 * @param character The character to add.
 * @return Result indicating success or memory error.
 */
Result add_character_to_buffer(Character character);

/**
 * Removes a character from the buffer at the current cursor position.
 * If the cursor is at the start of a line, it merges the current line with the previous one.
 *
 * @return Result indicating success or invalid argument.
 */
Result backspace_character_from_buffer();

/**
 * Removes a word from the buffer by backspacing from the current cursor position.
 * Stops at the beginning of the line or when a space/tab is encountered.
 *
 * @return Result indicating success or invalid argument.
 */
Result backspace_word_from_buffer();

/**
 * Deletes a character from the buffer at the current cursor position.
 * If the cursor is at the end of a line, it merges the current line with the next one.
 *
 * @return Result indicating success or does not exist if nothing to delete.
 */
Result delete_character_from_buffer();

/**
 * Deletes a word from the buffer starting at the current cursor position.
 * Stops at the end of the line or when a space/tab is encountered.
 *
 * @return Result indicating success or does not exist if nothing to delete.
 */
Result delete_word_from_buffer();

/**
 * Adds a new line to the buffer at the current cursor position.
 * If the cursor is in the middle of a line, the characters after the cursor
 * are moved to the new line.
 *
 * @return Result indicating success or memory error.
 */
Result add_new_line_to_buffer();

#endif // BUFFER_H
