#ifndef CURSOR_H
#define CURSOR_H

#include <stdbool.h>

#include "../utils/result.h"
#include "key.h"

/**
 * @brief Represents a cursor with its position, visibility, and blink counter.
 */
typedef struct Cursor {
    uint64_t column;  /**< The column position of the cursor. */
    uint64_t line;    /**< The line position of the cursor. */
    uint64_t counter; /**< The counter used for blinking the cursor. */
    bool     visible; /**< Indicates whether the cursor is visible. */
} Cursor;

/**
 * @brief Updates the cursor's blink state.
 *
 * Decrements the cursor's counter and toggles its visibility when the counter reaches zero.
 * Resets the counter to 30 after toggling visibility.
 *
 * @param cursor Pointer to the Cursor structure to update.
 */
void tick_cursor(Cursor *cursor);

/**
 * @brief Makes the cursor visible and resets its blink counter.
 *
 * Sets the cursor's visibility to true and resets the counter to 30.
 *
 * @param cursor Pointer to the Cursor structure to update.
 */
void set_visible(Cursor *cursor);

/**
 * @brief Makes the cursor invisible and resets its blink counter.
 *
 * Sets the cursor's visibility to false and resets the counter to 30.
 *
 * @param cursor Pointer to the Cursor structure to update.
 */
void set_invisible(Cursor *cursor);

#endif // CURSOR_H
