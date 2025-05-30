#include <stdint.h>

#include "text_renderer.h"
#include "../drivers/graphics.h"
#include "../model/character.h"
#include "font16x32.h"

void draw_character(uint16_t x, uint16_t y, Character character, uint32_t color) {
    for (int row = 0; row < FONT_HEIGHT; row++) {
        uint16_t pixels = font16x32[character][row];
        for (int col = 0; col < FONT_WIDTH; col++)
            if (pixels & (1 << (FONT_WIDTH - 1 - col))) res_vg_draw_pixel(x + col, y + row, color);
    }
}

void draw_string(uint16_t x, uint16_t y, uint32_t color, Character text[], uint64_t length) {
    while (length) {
        draw_character(x, y, *(text++), color);
        x += FONT_WIDTH;
        length--;
    }
}
