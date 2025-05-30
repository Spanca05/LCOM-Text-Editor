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
Result set_text_mode();

/**
 * @brief Sets the graphics mode using VBE.
 * @param submode The VBE mode to set.
 * @return Result indicating success or specific error.
 */
Result set_graphic_mode(uint16_t submode);

/**
 * @brief Initializes the video graphics mode.
 * @param mode The VBE mode to initialize.
 * @param video_memory Pointer to store the mapped video memory address.
 * @return Result indicating success or specific error.
 */
Result res_vg_init(uint16_t mode);

/**
 * @brief Allocates and initializes a back buffer for double buffering.
 * @return Result indicating success or specific error.
 *         - RES_OK: Successfully initialized the back buffer.
 *         - RES_MEMORY_ERROR: Failed to allocate memory for the back buffer.
 *         - RES_UNINITIALIZED: Framebuffer size is not initialized.
 */
Result init_backbuffer();

/**
 * @brief Frees the allocated back buffer.
 * @return Result indicating success or specific error.
 *         - RES_OK: Successfully freed the back buffer.
 */
Result free_backbuffer();

/**
 * @brief Swaps the back buffer with the video buffer.
 *
 * Copies the contents of the back buffer to the video buffer, effectively
 * displaying the back buffer on the screen.
 *
 * @return Result indicating success or specific error.
 *         - RES_OK: Successfully swapped buffers.
 *         - RES_UNINITIALIZED: Either the video buffer or back buffer is not initialized.
 *         - RES_MEMORY_ERROR: Failed to copy data between buffers.
 */
Result swap_buffers();

/**
 * @brief Retrieves the size in bytes of the current video frame buffer.
 *
 * This function calculates the size of the frame buffer based on the current
 * video mode settings. It ensures that the size is initialized before returning
 * the value.
 *
 * @param size Pointer to store the size of the frame buffer in bytes.
 * @return Result indicating success or specific error.
 *         - RES_OK: Successfully retrieved the frame buffer size.
 *         - RES_INVALID_ARGUMENT: The provided pointer is NULL.
 *         - RES_UNINITIALIZED: The frame buffer size has not been initialized.
 */
Result get_framebuffer_size(uint32_t *size);

/**
 * @brief Normalizes a color value based on the current mode.
 * @param color The color value to normalize.
 * @return Normalized color value.
 */
Result res_normalize_color(uint32_t *color);

/**
 * @brief Draws a pixel at the specified coordinates.
 * @param buf The buffer where the pixel will be written.
 * @param x The x-coordinate.
 * @param y The y-coordinate.
 * @param color The color of the pixel.
 * @return Result indicating success or specific error.
 */
Result res_vg_draw_pixel(uint16_t x, uint16_t y, uint32_t color);

/**
 * @brief Draws a horizontal line starting at the specified coordinates.
 * @param buf The buffer where the line will be drawn.
 * @param x The starting x-coordinate.
 * @param y The y-coordinate.
 * @param len The length of the line.
 * @param color The color of the line.
 * @return Result indicating success or specific error.
 */
Result res_vg_draw_hline(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

/**
 * @brief Draws a rectangle starting at the specified coordinates.
 * @param buf The buffer where the rectangle will be drawn.
 * @param x The starting x-coordinate.
 * @param y The starting y-coordinate.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 * @param color The color of the rectangle.
 * @return Result indicating success or specific error.
 */
Result res_vg_draw_rectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

#endif
