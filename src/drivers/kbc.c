#include "kbc.h"
#include "../utils/result.h"
#include "../utils/utils.h"
#include "i8042.h"
#include <lcom/lcf.h>
#include <stdbool.h>

Result(read_KBC_status)(uint8_t *status) {
    if (status == NULL) return RES_INVALID_ARGUMENT;
    if (res_util_sys_inb(KBC_STATUS_REG, status) != RES_OK) return RES_IO_ERROR;
    return RES_OK;
}

Result(write_KBC_command)(uint8_t port, uint8_t dataByte) {
    if (port != KBC_CMD_REG && port != KBC_IN_BUF) return RES_INVALID_ARGUMENT;

    uint8_t status;
    uint8_t attempts = 10;

    while (attempts) {
        if (read_KBC_status(&status) != RES_OK) return RES_IO_ERROR;
        if (INPUT_BUFFER_FULL(status)) {
            tickdelay(micros_to_ticks(20000));
            attempts--;
            continue;
        }
        if (sys_outb(port, dataByte) != RES_OK) return RES_IO_ERROR;
        return RES_OK;
    }
    return RES_TIMEOUT;
}

Result(read_KBC_output)(uint8_t port, uint8_t *output, bool mouse) {
    if (port != KBC_CMD_REG && port != KBC_OUT_BUF) return RES_INVALID_ARGUMENT;
    if (output == NULL) return RES_INVALID_ARGUMENT;

    uint8_t status;
    uint8_t attempts = 10;

    while (attempts) {
        if (read_KBC_status(&status) != RES_OK) return RES_IO_ERROR;
        if (!OUTPUT_BUFFER_FULL(status)) {
            tickdelay(micros_to_ticks(20000));
            attempts--;
            continue;
        }

        uint8_t temp_output;
        if (res_util_sys_inb(port, &temp_output) != RES_OK) return RES_IO_ERROR;
        if (PARITY_ERROR(status) || TIMEOUT_ERROR(status)) return RES_HARDWARE_ERROR;
        if (mouse && !(status & BIT(5))) return RES_IO_ERROR;
        if (!mouse && (status & BIT(5))) return RES_IO_ERROR;

        *output = temp_output;
        return RES_OK;
    }

    return RES_TIMEOUT;
}
