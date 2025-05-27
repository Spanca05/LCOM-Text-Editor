#ifndef _LCOM_GRAPHICS_H_
#define _LCOM_GRAPHICS_H_

#include "../utils/result.h"
#include <lcom/lcf.h>
#include <lcom/pixmap.h>

// Global variable to store VBE mode information
extern vbe_mode_info_t mode_info;

/**
 * @brief Sets the text mode.
 * @return Result indicating success or specific error.
 */
Result(set_text_mode)();

/**
 * @brief Sets the graphics mode using VBE.
 * @param submode The VBE mode to set.
 * @return Result indicating success or specific error.
 */
Result(set_graphic_mode)(uint16_t submode);

Result(res_vg_init)(uint16_t mode, void **video_memory);

Result(res_vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);
Result(res_vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);
Result(res_vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

Result(res_normalize_color)(uint32_t *color);

#endif
