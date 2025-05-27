#ifndef _LCOM_KBC_H_
#define _LCOM_KBC_H_

#include "../utils/result.h"
#include <lcom/lcf.h>
#include <stdbool.h>

/**
 * @brief Reads the status register of the keyboard controller.
 * @param status Pointer to store the status byte.
 * @return Result indicating success or specific error.
 */
Result(read_KBC_status)(uint8_t *status);

/**
 * @brief Writes a command byte to the keyboard controller.
 * @param port The port to write to (KBC_WRITE_CMD_BYTE for data, KBC_WRITE_CMD_PORT for command).
 * @param commandByte The command byte to write.
 * @return Result indicating success or specific error.
 */
Result(write_KBC_command)(uint8_t port, uint8_t dataByte);

/**
 * @brief Reads the output buffer of the keyboard controller.
 * @param port The port to read from (KBC_OUT_BUF for data, KBC_CMD_REG for status).
 * @param output Pointer to store the output byte.
 * @param mouse Flag indicating whether the output is from the mouse.
 * @return Result indicating success or specific error.
 */
Result(read_KBC_output)(uint8_t port, uint8_t *output, bool mouse);

#endif
