#ifndef BACKBUFFER_H
#define BACKBUFFER_H

#include "../utils/result.h"

/**
 * @brief Initializes the backbuffer.
 *
 * Allocates memory for the backbuffer based on the current video mode.
 *
 * @param buffer Output pointer to receive the allocated backbuffer.
 * @return Result indicating success or specific error:
 *         - RES_OK: Backbuffer successfully allocated.
 *         - RES_INVALID_ARGUMENT: Provided pointer is NULL.
 *         - RES_MEMORY_ERROR: Allocation failed.
 */
Result(init_backbuffer)(void **buffer);

/**
 * @brief Frees the backbuffer.
 *
 * Releases the memory allocated for the backbuffer.
 *
 * @param buffer Pointer returned by init_backbuffer.
 * @return Result indicating success or specific error.
 *         - RES_OK: Successfully freed the backbuffer.
 *         - RES_INVALID_ARGUMENT: The provided pointer is NULL.
 *         - RES_ERROR: Failed to free the backbuffer.
 */
Result(free_backbuffer)(void *buffer);

/**
 * @brief Swaps the backbuffer with the front buffer.
 *
 * Copies the contents of the backbuffer to the front buffer for rendering.
 *
 * @param buffer Pointer to the backbuffer to swap.
 * @return Result indicating success or specific error.
 *         - RES_OK: Successfully swapped buffers.
 *         - RES_IO_ERROR: Failed to swap buffers due to I/O error.
 */
Result(swap_buffers)(void *buffer);

#endif
