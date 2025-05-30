/**
 * @file font16x32.h
 * @brief Bitmap font data for 8x16 pixel ASCII characters (alternative set).
 *
 * Defines a 256-entry array where each entry is a 16-row bitmap
 * representing the 8x16 pixel glyph for an ASCII code.
 */

#ifndef FONT16X32_H
#define FONT16X32_H

#include <stdint.h>

/**
 * @brief Width of each character glyph in pixels.
 */
#define FONT_WIDTH 16

/**
 * @brief Height of each character glyph in pixels.
 */
#define FONT_HEIGHT 32

/**
 * @brief Font bitmap data (alternative set).
 *
 * font16x32[c][r] contains the 16-bit horizontal row r of the glyph for ASCII code c.
 */
extern const uint16_t font16x32[152][32];

#endif // FONT16X32_H
