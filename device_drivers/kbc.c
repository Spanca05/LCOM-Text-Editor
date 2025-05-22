#include "../utils/result.h"
#include <lcom/lcf.h>

#include "i8042.h"
#include "kbc.h"

/**
 * @brief Reads the status register of the keyboard controller.
 * @param status Pointer to store the status byte.
 * @return Result indicating success or specific error.
 */
Result(read_KBC_status)(uint8_t *status) {
    if (status == NULL) return RES_INVALID_ARGUMENT;

    if (util_sys_inb(0x64, status) != RES_OK) return RES_IO_ERROR;
    return RES_OK;
}

/**
 * @brief Reads the output buffer of the keyboard controller.
 * @param port The port to read from (0x60 for data, 0x64 for status).
 * @param output Pointer to store the output byte.
 * @param mouse Flag indicating whether the output is from the mouse.
 * @return Result indicating success or specific error.
 */
Result(read_KBC_output)(uint8_t port, uint8_t *output, uint8_t mouse) {
    if (output == NULL) return RES_INVALID_ARGUMENT;

    uint8_t status;
    uint8_t attempts = 10;

    while (attempts) {
        if (read_KBC_status(&status) != RES_OK) return RES_IO_ERROR;

        if (!(status & BIT(0))) {
            tickdelay(micros_to_ticks(20000));
            attempts--;
            continue;
        }

        uint8_t temp_output;
        if (util_sys_inb(port, &temp_output) != RES_OK) return RES_IO_ERROR;

        if (status & BIT(7) || status & BIT(6)) return RES_HARDWARE_ERROR;

        if (!(status & BIT(0))) return RES_IO_ERROR;

        if (mouse && !(status & BIT(5))) return RES_IO_ERROR;

        if (!mouse && (status & BIT(5))) return RES_IO_ERROR;

        *output = temp_output;
        return RES_OK;
    }

    return RES_TIMEOUT;
}

/**
 * @brief Writes a command byte to the keyboard controller.
 * @param port The port to write to (0x60 for data, 0x64 for command).
 * @param commandByte The command byte to write.
 * @return Result indicating success or specific error.
 */
Result(write_KBC_command)(uint8_t port, uint8_t commandByte) {
    uint8_t status;
    uint8_t attempts = 10;

    while (attempts) {
        if (read_KBC_status(&status) != RES_OK) return RES_IO_ERROR;

        if (status & BIT(1)) {
            tickdelay(micros_to_ticks(20000));
            attempts--;
            continue;
        }

        if (sys_outb(port, commandByte) != RES_OK) return RES_IO_ERROR;

        return RES_OK;
    }
    return RES_TIMEOUT;
}
