#ifndef _LCOM_GRAPHICS_H_
#define _LCOM_GRAPHICS_H_

#include <lcom/lcf.h>
#include "VBE.h"

vbe_mode_info_t mode_info;
uint8_t *frame_buffer;

int (set_graphic_mode)(uint16_t submode);
int (set_text_mode)();

#endif
