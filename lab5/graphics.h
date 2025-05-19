#ifndef _LCOM_GRAPHICS_H_
#define _LCOM_GRAPHICS_H_

#include <lcom/lcf.h>
#include <lcom/pixmap.h> // Use system header

extern vbe_mode_info_t mode_info;

int (set_graphic_mode)(uint16_t submode);
int (set_text_mode)();
int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);
int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);
int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);
uint32_t normalize_color(uint32_t color);

#endif
