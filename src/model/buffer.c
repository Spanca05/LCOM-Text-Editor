#include <stddef.h>
#include <stdio.h>

#include "buffer.h"
#include "character.h"
#include "line.h"

// Buffer State
static Buffer buffer;

void init_buffer() {
    // Init cursor
    buffer.cursor.column  = 1;
    buffer.cursor.line    = 1;
    buffer.cursor.counter = 60;
    buffer.cursor.visible = false;

    // Init first line
    Line *lines = (Line *)malloc(BUFFER_SEGMENT_SIZE * sizeof(Line));
    if (!lines) return RES_MEMORY_ERROR;

    // Update buffer state
    buffer.lines    = lines;
    buffer.capacity = BUFFER_SEGMENT_SIZE;
}

Result increase_buffer_size() {
    // Allocate space for lines
    size_t new_capacity = buffer.capacity + BUFFER_SEGMENT_SIZE;
    Line  *new_lines    = realloc(buffer.lines, new_capacity * sizeof(Line));
    if (!new_lines) return RES_MEMORY_ERROR;

    // Update buffer state
    buffer.lines    = new_lines;
    buffer.capacity = new_capacity;

    return RES_OK;
}

Result increase_buffer_size_if_necessary() {
    if (buffer.length + 1 > buffer.capacity) return increase_buffer_size();
    return RES_OK;
}

Result add_line_at(uint64_t position) {
    Result result;

    // Increase buffer if necessary
    result = increase_buffer_size_if_necessary();
    if (result) return result;

    // If position is in the middle
    // Shift lines down
    if (position > 0 && position <= buffer.length)
        memmove(&buffer.lines[position], &buffer.lines[position - 1], (buffer.length - position + 1) * sizeof(Line));

    // If position is past the end of the buffer
    if (position < 0 || position > buffer.length + 1) return RES_INVALID_ARGUMENT;

    // Insert new line
    result = create_line(&buffer.lines[position - 1]);
    if (result) return result;

    // Update buffer length
    buffer.length++;

    return RES_OK;
}

Result remove_line_at(uint64_t position) {
    if (position == 0 || position > buffer.length) return RES_INVALID_ARGUMENT;

    // Shift lines up
    memmove(&buffer.lines[position - 1], &buffer.lines[position], (buffer.length - position) * sizeof(Line));

    // Update buffer length
    buffer.length--;

    return RES_OK;
}

void buffer_clock_tick() { tick_cursor(&buffer.cursor); }

Result update_cursor(Key key) {
    switch (key) {
    case KEY_ARROW_UP   : buffer.cursor.line--; break;
    case KEY_ARROW_DOWN : buffer.cursor.line++; break;
    case KEY_ARROW_LEFT : buffer.cursor.column--; break;
    case KEY_ARROW_RIGHT: buffer.cursor.column++; break;
    case KEY_ESC        : buffer.cursor.visible = false; return RES_OK;

    default: return RES_INVALID_ARGUMENT;
    }

    return RES_OK;
}

void add_character_to_buffer(Character character) {
    // TODO Do this properly

    add_character_at(&buffer.lines[0], character, buffer.lines[0].length + 1); // TEST CODE
}
