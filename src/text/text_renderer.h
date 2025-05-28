/**
 * @file text_renderer.h
 * @brief Text rendering utilities for drawing characters and strings in graphical mode.
 *
 * Provides functions to render characters and strings using a fixed 8x16 bitmap font.
 */

#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <stdint.h>

/**
 * @brief Draw a single character at a specific screen coordinate.
 *
 * Renders the given ASCII character using the 8x16 font bitmap.
 *
 * @param x The X (horizontal) pixel coordinate of the character's top-left.
 * @param y The Y (vertical) pixel coordinate of the character's top-left.
 * @param c The ASCII character to draw.
 * @param color The direct-color value to use when drawing the character.
 */
void draw_char(uint16_t x, uint16_t y, char c, uint32_t color);

/**
 * @brief Draw a null-terminated string at a specific screen coordinate.
 *
 * Renders each character in the provided string sequentially using
 * the 8x16 font bitmap.
 *
 * @param x The starting X (horizontal) pixel coordinate for the string.
 * @param y The starting Y (vertical) pixel coordinate for the string.
 * @param s The null-terminated string to draw.
 * @param color The direct-color value to use when drawing the text.
 */
void draw_string(uint16_t x, uint16_t y, const char *s, uint32_t color);

#endif // TEXT_RENDERER_H
