#ifndef UTILS_H
#define UTILS_H

#include "result.h"
#include <stdint.h>

#define BIT(n) (1 << (n))

Result(res_util_get_LSB)(uint16_t value, uint8_t *lsb);
Result(res_util_get_MSB)(uint16_t value, uint8_t *msb);
Result(res_util_sys_inb)(uint32_t address, uint8_t *value);

#endif // UTILS_H
