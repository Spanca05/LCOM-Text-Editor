#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "../model/character.h"
#include "line.h"

Result create_line(Line *line) {
    if (line == NULL) return RES_INVALID_ARGUMENT;

    // Allocate space for characters
    Character *data = (Character *)malloc(sizeof(Character) * LINE_SEGMENT_SIZE);
    if (data == NULL) return RES_MEMORY_ERROR;

    // Update line state
    line->data     = data;
    line->capacity = LINE_SEGMENT_SIZE;
    line->length   = 0;

    return RES_OK;
}

Result delete_line(Line *line) {
    if (line == NULL) return RES_INVALID_ARGUMENT;

    // Free the allocated memory for characters
    free(line->data);

    // Reset line state
    line->data     = NULL;
    line->capacity = 0;
    line->length   = 0;

    return RES_OK;
}

Result increase_line_size(Line *line) {
    if (line == NULL) return RES_INVALID_ARGUMENT;

    // Allocate space for characters
    uint64_t   newCapacity = line->capacity + LINE_SEGMENT_SIZE;
    Character *newData     = (Character *)realloc(line->data, newCapacity * sizeof(Character));
    if (newData == NULL) return RES_MEMORY_ERROR;

    // Update line state
    line->data     = newData;
    line->capacity = newCapacity;

    return RES_OK;
}

Result increase_line_if_necessary(Line *line) {
    if (line == NULL) return RES_INVALID_ARGUMENT;
    if (line->length + 1 > line->capacity) return increase_line_size(line);
    return RES_OK;
}

Result add_character_at(Line *line, Character character, uint64_t position) {
    if (line == NULL) return RES_INVALID_ARGUMENT;
    Result result;

    // Increase line if necessary
    result = increase_line_if_necessary(line);
    if (result) return result;

    // If insert is in the middle of the line
    // Shift characters to the right
    if (position > 0 && position <= line->length)
        memmove(&line->data[position], &line->data[position - 1], (line->length - position + 1) * sizeof(Character));

    // If position is past the end of the line
    if (position > line->length + 1) return RES_INVALID_ARGUMENT;

    // Insert the new character
    line->data[position - 1] = character;

    // Update line length
    line->length++;

    return RES_OK;
}

Result remove_character_at(Line *line, uint64_t position) {
    if (line == NULL) return RES_INVALID_ARGUMENT;
    if (position == 0 || position > line->length) return RES_INVALID_ARGUMENT;

    // Shift characters to the left
    memmove(&line->data[position - 1], &line->data[position], (line->length - position) * sizeof(Character));

    // Update line length
    line->length--;

    return RES_OK;
}
