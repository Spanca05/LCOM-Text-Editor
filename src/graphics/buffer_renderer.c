#include <stdint.h>

#include "../drivers/graphics.h"
#include "../model/buffer.h"
#include "../utils/result.h"
#include "font16x32.h"
#include "text_renderer.h"

static uint64_t window_x = 0;
static uint64_t window_y = 0;

Result render_buffer(uint16_t y_offset) {
    uint64_t horizontal_cells = h_res / FONT_WIDTH;
    uint64_t vertical_cells   = (v_res - 2 * (FONT_HEIGHT + 4)) / FONT_HEIGHT;

    // Adjust window_x and window_y to ensure the cursor is visible
    if (text_buffer.cursor.column - 1 < window_x) window_x = text_buffer.cursor.column - 1;
    else if (text_buffer.cursor.column > window_x + horizontal_cells)
        window_x = text_buffer.cursor.column - horizontal_cells;

    if (text_buffer.cursor.line - 1 < window_y) window_y = text_buffer.cursor.line - 1;
    else if (text_buffer.cursor.line > window_y + vertical_cells) window_y = text_buffer.cursor.line - vertical_cells;

    if (text_buffer.cursor.visible)
        res_vg_draw_rectangle(
            (text_buffer.cursor.column - 1 - window_x) * FONT_WIDTH,
            y_offset + (text_buffer.cursor.line - 1 - window_y) * FONT_HEIGHT, FONT_WIDTH, FONT_HEIGHT, 0xFFFFFF
        );

    // Draw each character in the buffer within the drawing area
    for (uint64_t lineN = 0; lineN < text_buffer.length; lineN++) {
        uint16_t y = y_offset + (lineN - window_y) * FONT_HEIGHT;

        // Skip rendering if it overlaps the restricted area
        if (y < (FONT_HEIGHT + 4)) continue;
        if (y + FONT_HEIGHT > v_res - (FONT_HEIGHT + 4)) continue;

        Line *line = &text_buffer.lines[lineN];
        for (uint16_t col = 0; col < line->length; col++) {
            uint16_t x = (col - window_x) * FONT_WIDTH;
            if (lineN + 1 == text_buffer.cursor.line && col + 1 == text_buffer.cursor.column
                && text_buffer.cursor.visible)
                draw_character(x, y, line->data[col], 0x333333);
            else draw_character(x, y, line->data[col], 0xFFFFFF);
        }
    }

    return RES_OK;
}
