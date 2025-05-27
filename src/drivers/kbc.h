#ifndef _LCOM_KBC_H_
#define _LCOM_KBC_H_

#include "../utils/result.h"
#include <lcom/lcf.h>

Result(read_KBC_status)(uint8_t *status);

Result(write_KBC_command)(uint8_t port, uint8_t commandByte);

Result(read_KBC_output)(uint8_t port, uint8_t *output, uint8_t mouse);

#endif
