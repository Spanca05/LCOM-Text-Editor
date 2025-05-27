#ifndef _LCOM_KBD_H_
#define _LCOM_KBD_H_

#include "../utils/result.h"
#include <lcom/lcf.h>

/**
 * @brief Handles keyboard interrupts and retrieves the scancode.
 *
 * This function reads the keyboard status register and output buffer to
 * retrieve the scancode of the key pressed or released. It handles both
 * single-byte and two-byte scancodes.
 *
 * @param scancode Pointer to store the retrieved scancode.
 * @return Result indicating success or specific error:
 *         - RES_OK: Scancode successfully retrieved.
 *         - RES_IO_ERROR: I/O error occurred.
 *         - RES_TIMEOUT: Timeout error occurred.
 *         - RES_ERROR: No data available in the output buffer.
 *         - RES_NOT_READY: Waiting for the second byte of a two-byte scancode.
 */
Result(keyboard_ih)(uint16_t *scancode);

/**
 * @brief Subscribes to keyboard interrupts.
 * @param bit_no Pointer to store the bit number of the interrupt.
 * @return Result indicating success or specific error.
 */
Result(keyboard_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes from keyboard interrupts.
 * @return Result indicating success or specific error.
 */
Result(keyboard_unsubscribe_int)();

/**
 * @brief Restores the keyboard controller to its default state.
 * @return Result indicating success or specific error.
 */
Result(kbc_restore)();

#endif
