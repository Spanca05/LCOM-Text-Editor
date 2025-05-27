#include <lcom/lcf.h>

#include "result.h"
#include <stdint.h>

extern int sys_inb_count;

Result(res_util_get_LSB)(uint16_t value, uint8_t *lsb) {
    if (lsb == NULL) return RES_INVALID_ARGUMENT;

    *lsb = (uint8_t)(value & 0xFF);
    return RES_OK;
}

Result(res_util_get_MSB)(uint16_t value, uint8_t *msb) {
    if (msb == NULL) return RES_INVALID_ARGUMENT;

    *msb = (uint8_t)((value >> 8) & 0xFF);
    return RES_OK;
}

Result(res_util_sys_inb)(uint32_t address, uint8_t *value) {
    uint32_t val;

    if (sys_inb(address, &val) != RES_OK) return RES_IO_ERROR;

    *value = (uint8_t)val;
    return RES_OK;
}
