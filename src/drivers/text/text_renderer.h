#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <stdint.h>

// Draw a single character at (x, y) using the 8x16 font
void draw_char(uint16_t x, uint16_t y, char c, uint32_t color);

// Draw a null-terminated string starting at (x, y)
void draw_string(uint16_t x, uint16_t y, const char *s, uint32_t color);

#endif // TEXT_RENDERER_H