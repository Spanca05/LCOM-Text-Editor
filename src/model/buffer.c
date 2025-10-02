#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../files/write_utf8_file.h"
#include "buffer.h"
#include "character.h"
#include "line.h"

// Buffer State
Buffer text_buffer;

Result init_buffer() {
    // Init cursor
    text_buffer.cursor.column    = 1;
    text_buffer.cursor.line      = 1;
    text_buffer.cursor.counter   = 60;
    text_buffer.cursor.visible   = false;
    text_buffer.autosave_counter = 100;

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

void buffer_clock_tick() {
    // Update cursor counter
    tick_cursor(&text_buffer.cursor);

    // Update autosave counter
    text_buffer.autosave_counter--;
    if (text_buffer.autosave_counter <= 0) {
        text_buffer.autosave_counter = 100;
        write_utf8_file("notes.txt");
    }
}

Result move_cursor_up() {
    set_visible(&text_buffer.cursor);

    // Do nothing if on the first line
    if (text_buffer.cursor.line == 1) {
        text_buffer.cursor.column = 1;
        return RES_OK;
    }

    Line *previous_line = &text_buffer.lines[text_buffer.cursor.line - 2];

    // Previous line is smaller
    if (text_buffer.cursor.column > previous_line->length) text_buffer.cursor.column = previous_line->length + 1;

    text_buffer.cursor.line--;
    return RES_OK;
}

Result move_cursor_down() {
    set_visible(&text_buffer.cursor);

    // Do nothing if on the last line
    if (text_buffer.cursor.line == text_buffer.length) {
        text_buffer.cursor.column = text_buffer.lines[text_buffer.length - 1].length + 1;
        return RES_OK;
    }

    Line *next_line = &text_buffer.lines[text_buffer.cursor.line];

    // Next line is smaller
    if (text_buffer.cursor.column > next_line->length) text_buffer.cursor.column = next_line->length + 1;

    text_buffer.cursor.line++;
    return RES_OK;
}

Result move_cursor_left() {
    set_visible(&text_buffer.cursor);

    // If at the start of the line, move to the end of the previous line
    if (text_buffer.cursor.column == 1) {
        if (text_buffer.cursor.line == 1) return RES_DOES_NOT_EXIST; // Already at the start of the buffer

        text_buffer.cursor.line--;
        text_buffer.cursor.column = text_buffer.lines[text_buffer.cursor.line - 1].length + 1;
    } else {
        // Move one character to the left
        text_buffer.cursor.column--;
    };
    return RES_OK;
}

Result move_cursor_right() {
    set_visible(&text_buffer.cursor);

    // If at the end of the line, move to the start of the next line
    if (text_buffer.cursor.column > text_buffer.lines[text_buffer.cursor.line - 1].length) {
        if (text_buffer.cursor.line == text_buffer.length)
            return RES_DOES_NOT_EXIST; // Already at the end of the buffer

        text_buffer.cursor.line++;
        text_buffer.cursor.column = 1;
    } else {
        // Move one character to the right
        text_buffer.cursor.column++;
    }
    return RES_OK;
}

Result add_character_to_buffer(Character character) {
    set_visible(&text_buffer.cursor);
    Result result;

    // Add Character to buffer
    result = add_character_at(&text_buffer.lines[text_buffer.cursor.line - 1], character, text_buffer.cursor.column);
    if (result != RES_OK) return result;

    // Update cursor position
    text_buffer.cursor.column++;

    return RES_OK;
}

Result backspace_character_from_buffer() {
    set_visible(&text_buffer.cursor);
    Result result;

    // If on the start of the line
    if (text_buffer.cursor.column == 1 && text_buffer.cursor.line != 1) {
        // Move cursor to the end of the previous line
        text_buffer.cursor.line--;
        text_buffer.cursor.column = text_buffer.lines[text_buffer.cursor.line - 1].length + 1;

        // Copy characters from the current line to the previous line
        Line *current_line  = &text_buffer.lines[text_buffer.cursor.line];
        Line *previous_line = &text_buffer.lines[text_buffer.cursor.line - 1];

        for (size_t i = 0; i < current_line->length; i++) {
            result = add_character_at(previous_line, current_line->data[i], previous_line->length + 1);
            if (result) return result;
        }

        // Remove the current line
        return remove_line_at(text_buffer.cursor.line + 1);
    }

    // Remove Character from buffer
    result = remove_character_at(&text_buffer.lines[text_buffer.cursor.line - 1], text_buffer.cursor.column - 1);
    if (result) return result;

    // Update cursor position
    text_buffer.cursor.column--;

    return RES_OK;
}

Result backspace_word_from_buffer() {
    set_visible(&text_buffer.cursor);
    Result result;

    // If at the beginning of the line, do nothing
    if (text_buffer.cursor.column == 1) return RES_OK;

    // Move cursor left and delete characters until a space, tab, or beginning of the line is found
    do {
        result = backspace_character_from_buffer();
        if (result != RES_OK) return result;

        if (text_buffer.cursor.column == 1) break;

        Character prev_char = text_buffer.lines[text_buffer.cursor.line - 1].data[text_buffer.cursor.column - 2];
        if (prev_char == CHAR_SPACE || prev_char == CHAR_TAB) break;
    } while (true);

    return RES_OK;
}

Result delete_character_from_buffer() {
    set_visible(&text_buffer.cursor);
    Result result;

    // If at the end of the line
    if (text_buffer.cursor.column > text_buffer.lines[text_buffer.cursor.line - 1].length) {
        // If not the last line, merge with the next line
        if (text_buffer.cursor.line != text_buffer.length) {
            Line *current_line = &text_buffer.lines[text_buffer.cursor.line - 1];
            Line *next_line    = &text_buffer.lines[text_buffer.cursor.line];

            // Copy characters from the next line to the current line
            for (size_t i = 0; i < next_line->length; i++) {
                result = add_character_at(current_line, next_line->data[i], current_line->length + 1);
                if (result) return result;
            }

            // Remove the next line
            return remove_line_at(text_buffer.cursor.line + 1);
        } else return RES_DOES_NOT_EXIST; // Nothing to delete
    }

    // Remove Character from buffer at the cursor position
    result = remove_character_at(&text_buffer.lines[text_buffer.cursor.line - 1], text_buffer.cursor.column);
    if (result) return result;

    // Cursor position remains unchanged
    return RES_OK;
}

Result delete_word_from_buffer() {
    set_visible(&text_buffer.cursor);
    Result result;

    // If at the end of the line, do nothing
    if (text_buffer.cursor.column > text_buffer.lines[text_buffer.cursor.line - 1].length) return RES_OK;

    // Delete characters until a space, tab, or end of the line is found
    do {
        result = delete_character_from_buffer();
        if (result != RES_OK) return result;

        if (text_buffer.cursor.column > text_buffer.lines[text_buffer.cursor.line - 1].length) break;

        Character next_char = text_buffer.lines[text_buffer.cursor.line - 1].data[text_buffer.cursor.column - 1];
        if (next_char == CHAR_SPACE || next_char == CHAR_TAB) break;
    } while (true);

    return RES_OK;
}

Result add_new_line_to_buffer() {
    set_visible(&text_buffer.cursor);
    Result result;

    result = add_line_at(text_buffer.cursor.line + 1);
    if (result) return result;

    // If cursor is in the middle of the line
    if (text_buffer.cursor.column <= text_buffer.lines[text_buffer.cursor.line - 1].length) {
        // Copy characters from the current line to the new line
        Line *current_line = &text_buffer.lines[text_buffer.cursor.line - 1];
        Line *new_line     = &text_buffer.lines[text_buffer.cursor.line];

        for (size_t i = text_buffer.cursor.column - 1; i < current_line->length; i++) {
            result = add_character_at(new_line, current_line->data[i], new_line->length + 1);
            if (result) return result;
        }

        // Remove characters from the current line after the cursor
        current_line->length = text_buffer.cursor.column - 1;
    }

    // Update cursor position
    text_buffer.cursor.line++;
    text_buffer.cursor.column = 1;

    return RES_OK;
}
