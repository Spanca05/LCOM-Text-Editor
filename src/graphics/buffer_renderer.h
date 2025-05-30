#ifndef BUFFER_RENDERER_H
#define BUFFER_RENDERER_H

#include <stdint.h>

#include "../utils/result.h"

/**
 * @brief Renders the text buffer to the screen.
 *
 * Draws the text buffer's content, including the cursor if it is visible,
 * starting from the specified vertical offset.
 *
 * @param y_offset The vertical offset in pixels where the rendering starts.
 * @return Result indicating success or specific error.
 */
Result render_buffer(uint16_t y_offset);

#endif // BUFFER_RENDERER_H
