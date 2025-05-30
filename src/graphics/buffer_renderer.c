#include <stdint.h>

#include "../drivers/graphics.h"
#include "../model/buffer.h"
#include "../utils/result.h"
#include "font16x32.h"
#include "text_renderer.h"

Result render_buffer(uint16_t y_offset) {
    if (text_buffer.cursor.visible)
        res_vg_draw_rectangle(
            (text_buffer.cursor.column - 1) * FONT_WIDTH, y_offset + (text_buffer.cursor.line - 1) * FONT_HEIGHT,
            FONT_WIDTH, FONT_HEIGHT, 0xFFFFFF
        );

    // Draw each character in the buffer within the drawing area
    for (uint64_t lineN = 0; lineN < text_buffer.length; lineN++) {
        Line *line = &text_buffer.lines[lineN];

        for (uint16_t col = 0; col < line->length; col++) {
            uint16_t x = col * FONT_WIDTH;
            uint16_t y = y_offset + lineN * FONT_HEIGHT;
            if (lineN + 1 == text_buffer.cursor.line && col + 1 == text_buffer.cursor.column
                && text_buffer.cursor.visible)
                draw_character(x, y, line->data[col], 0x333333);
            else draw_character(x, y, line->data[col], 0xFFFFFF);
        }
    }

    return RES_OK;
}
