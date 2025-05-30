#include "text_renderer.h"
#include "../drivers/graphics.h"
#include "font16x32.h"

#define FONT_WIDTH  16
#define FONT_HEIGHT 32

void draw_character(void *buf, uint16_t x, uint16_t y, char c, uint32_t color) {
    for (int row = 0; row < FONT_HEIGHT; row++) {
        // font16x32 stores glyph in high byte of 16-bit row
        uint16_t pixels = (uint16_t)(font16x32[(uint8_t)c][row]);
        for (int col = 0; col < FONT_WIDTH; col++) {
            if (pixels & (1 << (FONT_WIDTH - 1 - col))) res_vg_draw_pixel(buf, x + col, y + row, color);
        }
    }
}

void draw_string(void *buf, uint16_t x, uint16_t y, const char *s, uint32_t color) {
    while (*s) {
        draw_character(buf, x, y, *s++, color);
        x += FONT_WIDTH;
    }
}

void draw_menu(void *buf, uint16_t x, uint16_t y, const char *filenames[], int *num_files, uint32_t color) {
    draw_string(buf, x, y, "Files:\n", color);
    if (*num_files == 0)
    {
        draw_string(buf, x, y, "No files available.:\n", color);
    }
    else if (*num_files > 0)
    {
        for (int i = 1; i <= *num_files; i++)
        {
            char *s = malloc(sizeof(filenames[i]) + 10);
            sprintf(s, "%d) %s\n", i, filenames[i]);
            draw_string(buf,x,y,s,color);
        }
        
    }
    draw_string(buf, x, y, "Create a new one!:\n", color);
}
