#ifndef BUFFER_H
#define BUFFER_H

#include "character.h"
#include "cursor.h"
#include "line.h"

#define BUFFER_SEGMENT_SIZE 100

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
void init_buffer();

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
 * Updates the cursor's position based on the given key input.
 *
 * @param key The key input to update the cursor.
 * @return Result indicating success or invalid argument.
 */
Result update_cursor(Key key);

/**
 * Adds a character to the buffer at the current cursor position.
 *
 * @param character The character to be added.
 */
void add_character_to_buffer(Character character);

#endif // BUFFER_H
