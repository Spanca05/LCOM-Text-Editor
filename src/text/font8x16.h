/**
 * @file font8x16.h
 * @brief Bitmap font data for 8x16 pixel ASCII characters.
 *
 * Defines a 256-entry array where each entry is a 16-row bitmap
 * representing the 8x16 pixel glyph for an ASCII code.
 */

#ifndef FONT8X16_H
#define FONT8X16_H

#include <stdint.h>

/**
 * @brief Width of each character glyph in pixels.
 */
#define FONT_WIDTH 8

/**
 * @brief Height of each character glyph in pixels.
 */
#define FONT_HEIGHT 16

/**
 * @brief Font bitmap data.
 *
 * font8x16[c][r] contains the 8-bit horizontal row r of the glyph for ASCII code c.
 */
extern const uint8_t font8x16[256][FONT_HEIGHT];

#endif // FONT8X16_H