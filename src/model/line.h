#ifndef LINE_H
#define LINE_H

#include <stdint.h>

#include "../model/character.h"

#define LINE_SEGMENT_SIZE 100

typedef struct Line {
    Character *data;
    uint64_t   capacity;
    uint64_t   length;
} Line;

/**
 * @brief Creates a new Line structure with initial capacity.
 *
 * @param line Pointer to the Line structure to initialize.
 * @return Result indicating success or failure.
 */
Result create_line(Line *line);

/**
 * @brief Deletes a Line structure and frees its allocated memory.
 *
 * @param line Pointer to the Line structure to delete.
 * @return Result indicating success or failure.
 */
Result delete_line(Line *line);

/**
 * @brief Increases the capacity of a Line structure by LINE_SEGMENT_SIZE.
 *
 * @param line Pointer to the Line structure to resize.
 * @return Result indicating success or failure.
 */
Result increase_line_size(Line *line);

/**
 * @brief Increases the capacity of a Line structure if necessary.
 *
 * @param line Pointer to the Line structure to check and resize.
 * @return Result indicating success or failure.
 */
Result increase_line_if_necessary(Line *line);

/**
 * @brief Adds a character at a specific position in the Line.
 *
 * @param line Pointer to the Line structure.
 * @param character The Character to add.
 * @param position The position (1-based index) to insert the character.
 * @return Result indicating success or failure.
 */
Result add_character_at(Line *line, Character character, uint64_t position);

/**
 * @brief Removes a character at a specific position in the Line.
 *
 * @param line Pointer to the Line structure.
 * @param position The position (1-based index) of the character to remove.
 * @return Result indicating success or failure.
 */
Result remove_character_at(Line *line, uint64_t position);

#endif // LINE_H
