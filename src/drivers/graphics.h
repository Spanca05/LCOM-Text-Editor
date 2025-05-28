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

/**
 * @brief Initializes the video graphics mode.
 * @param mode The VBE mode to initialize.
 * @param video_memory Pointer to store the mapped video memory address.
 * @return Result indicating success or specific error.
 */
Result(res_vg_init)(uint16_t mode, void **video_memory);

/**
 * @brief Normalizes a color value based on the current mode.
 * @param color The color value to normalize.
 * @return Normalized color value.
 */
Result(res_normalize_color)(uint32_t *color);

/**
 * @brief Draws a pixel at the specified coordinates.
 * @param x The x-coordinate.
 * @param y The y-coordinate.
 * @param color The color of the pixel.
 * @return Result indicating success or specific error.
 */
Result(res_vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color);

/**
 * @brief Draws a horizontal line starting at the specified coordinates.
 * @param x The starting x-coordinate.
 * @param y The y-coordinate.
 * @param len The length of the line.
 * @param color The color of the line.
 * @return Result indicating success or specific error.
 */
Result(res_vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

/**
 * @brief Draws a rectangle starting at the specified coordinates.
 * @param x The starting x-coordinate.
 * @param y The starting y-coordinate.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 * @param color The color of the rectangle.
 * @return Result indicating success or specific error.
 */
Result(res_vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

/**
 * @brief Returns the size in bytes of the current video frame buffer.
 * @return Frame buffer size in bytes.
 */
uint32_t get_framebuffer_size(void);

#endif
