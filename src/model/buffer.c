#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"
#include "character.h"
#include "line.h"

// Buffer State
Buffer text_buffer;

Result init_buffer() {
    // Init cursor
    text_buffer.cursor.column  = 1;
    text_buffer.cursor.line    = 1;
    text_buffer.cursor.counter = 60;
    text_buffer.cursor.visible = false;

    // Init Lines array
    Line *lines = (Line *)malloc(BUFFER_SEGMENT_SIZE * sizeof(Line));
    if (!lines) return RES_MEMORY_ERROR;

    // Update buffer state
    text_buffer.lines    = lines;
    text_buffer.capacity = BUFFER_SEGMENT_SIZE;

    // Create first line
    create_line(&text_buffer.lines[0]);
    text_buffer.length = 1;

    return RES_OK;
}

Result increase_buffer_size() {
    // Allocate space for lines
    size_t new_capacity = text_buffer.capacity + BUFFER_SEGMENT_SIZE;
    Line  *new_lines    = realloc(text_buffer.lines, new_capacity * sizeof(Line));
    if (!new_lines) return RES_MEMORY_ERROR;

    // Update buffer state
    text_buffer.lines    = new_lines;
    text_buffer.capacity = new_capacity;

    return RES_OK;
}

Result increase_buffer_size_if_necessary() {
    if (text_buffer.length + 1 > text_buffer.capacity) return increase_buffer_size();
    return RES_OK;
}

Result add_line_at(uint64_t position) {
    Result result;

    // Increase buffer if necessary
    result = increase_buffer_size_if_necessary();
    if (result) return result;

    // If position is in the middle
    // Shift lines down
    if (position > 0 && position <= text_buffer.length)
        memmove(
            &text_buffer.lines[position], &text_buffer.lines[position - 1],
            (text_buffer.length - position + 1) * sizeof(Line)
        );

    // If position is past the end of the buffer
    if (position > text_buffer.length + 1) return RES_INVALID_ARGUMENT;

    // Insert new line
    result = create_line(&text_buffer.lines[position - 1]);
    if (result) return result;

    // Update buffer length
    text_buffer.length++;

    return RES_OK;
}

Result remove_line_at(uint64_t position) {
    if (position == 0 || position > text_buffer.length) return RES_INVALID_ARGUMENT;

    // Shift lines up
    memmove(
        &text_buffer.lines[position - 1], &text_buffer.lines[position], (text_buffer.length - position) * sizeof(Line)
    );

    // Update buffer length
    text_buffer.length--;

    return RES_OK;
}

void buffer_clock_tick() { tick_cursor(&text_buffer.cursor); }

Result update_cursor(Key key) {
    switch (key) {
    case KEY_ARROW_UP   : text_buffer.cursor.line--; break;
    case KEY_ARROW_DOWN : text_buffer.cursor.line++; break;
    case KEY_ARROW_LEFT : text_buffer.cursor.column--; break;
    case KEY_ARROW_RIGHT: text_buffer.cursor.column++; break;
    case KEY_ESC        : text_buffer.cursor.visible = false; return RES_OK;

    default: return RES_INVALID_ARGUMENT;
    }

    return RES_OK;
}

void add_character_to_buffer(Character character) {
    Result result;

    // Add Character to buffer
    result = add_character_at(&text_buffer.lines[text_buffer.cursor.line - 1], character, text_buffer.cursor.column);
    if (result != RES_OK) return;

    // Update cursor position
    text_buffer.cursor.column++;
}

void remove_character_from_buffer() {
    Result result;

    // Remove Character from buffer
    result = remove_character_at(&text_buffer.lines[text_buffer.cursor.line - 1], text_buffer.cursor.column - 1);
    if (result != RES_OK) return;

    // Update cursor position
    text_buffer.cursor.column--;
}

void add_new_line_to_buffer() {
    Result result;

    result = add_line_at(text_buffer.cursor.line + 1);
    if (result != RES_OK) return;

    // If cursor is in the middle of the line
    if (text_buffer.cursor.column <= text_buffer.lines[text_buffer.cursor.line - 1].length) {
        // Copy characters from the current line to the new line
        Line *current_line = &text_buffer.lines[text_buffer.cursor.line - 1];
        Line *new_line = &text_buffer.lines[text_buffer.cursor.line];

        for (size_t i = text_buffer.cursor.column - 1; i < current_line->length; i++) 
            add_character_at(new_line, current_line->data[i], new_line->length + 1);
        

        // Remove characters from the current line after the cursor
        current_line->length = text_buffer.cursor.column - 1;
    }

    // Update cursor position
    text_buffer.cursor.line++;
    text_buffer.cursor.column = 1;
}
