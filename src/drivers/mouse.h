#ifndef _LCOM_MOUSE_H_
#define _LCOM_MOUSE_H_

#include "../utils/result.h"
#include <lcom/lcf.h>

Result(mouse_subscribe_int)(uint8_t *bit_no);

Result(mouse_unsubscribe_int)();

void(mouse_ih)();

void(mouse_sync_bytes)();

void(mouse_bytes_to_packet)();

Result(mouse_write)(uint8_t command);

#endif
