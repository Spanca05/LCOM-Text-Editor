#include "text_renderer.h"
#include "../drivers/graphics.h"
#include "font8x16.h"

#define FONT_WIDTH  8
#define FONT_HEIGHT 16

void draw_char(uint16_t x, uint16_t y, char c, uint32_t color) {
    for (int row = 0; row < FONT_HEIGHT; row++) {
        uint16_t bits = font8x16[(uint8_t)c][row];
        for (int col = 0; col < FONT_WIDTH; col++) {
            if (bits & (1 << (FONT_WIDTH - 1 - col))) res_vg_draw_pixel(x + col, y + row, color);
        }
    }
}

void draw_string(uint16_t x, uint16_t y, const char *s, uint32_t color) {
    while (*s) {
        draw_char(x, y, *s++, color);
        x += FONT_WIDTH;
    }
}