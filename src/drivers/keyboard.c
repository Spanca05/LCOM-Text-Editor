#include "../utils/result.h"
#include "../utils/utils.h"
#include "i8042.h"
#include <lcom/lcf.h>

// Global variables for keyboard interrupt handling
int      keyboard_hook_id = 1;
uint16_t scancode         = 0xFFFF;
bool     complete_scan    = true; // Flag to indicate that we are waiting for the second byte

/**
 * @brief Interrupt handler for the keyboard controller (KBC).
 *
 * This function handles keyboard interrupts by reading the status register
 * and output buffer of the KBC. It processes scancodes, including handling
 * one-byte and two-byte scancodes, and checks for communication errors.
 *
 * The function performs the following steps:
 * 1. Reads the status register to check the KBC's state.
 * 2. Verifies if there are any communication errors (parity or timeout).
 * 3. Checks if the output buffer is full, indicating data is available.
 * 4. Reads the scancode from the output buffer.
 * 5. Determines if the scancode is one or two bytes long and processes it accordingly.
 *
 * @note If a two-byte scancode is detected (starting with 0xE0), the function
 *       sets a temporary state to wait for the second byte.
 *
 * @return Void. The function exits early if any error or invalid state is detected.
 */
void(kbc_ih)() {
    scancode = 0xFFFF;
    uint8_t status, byte;

    // Read status register
    if (res_util_sys_inb(KBC_STATUS_REG, &status) != RES_OK) return;

    // Check if there was some communication error
    if (PARITY_ERROR(status) || TIMEOUT_ERROR(status)) return;

    // Check if there is no data to be read
    if (!OUTPUT_BUFFER_FULL(status)) return;

    if (res_util_sys_inb(KBC_OUT_BUF, &byte) != RES_OK) return;

    // Check if scancode is one or two bytes long
    if (byte == 0xE0) {
        complete_scan = false;
        return;
    }

    // If scancode is two bytes long, we combine the values
    if (!complete_scan) scancode = (0xE0 << 8) | byte;
    else scancode = (0x00 << 8) | byte;
}

Result(kbd_subscribe_int)(uint8_t *bit_no) {
    if (bit_no == NULL) return RES_INVALID_ARGUMENT;

    *bit_no = BIT(keyboard_hook_id);
    if (sys_irqsetpolicy(KEYBOARD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &keyboard_hook_id) != 0)
        return RES_PERMISSION_ERROR;

    return RES_OK;
}

/**
 * @brief Unsubscribes from keyboard interrupts.
 * @return Result indicating success or specific error.
 */
Result(kbd_unsubscribe_int)() {
    if (sys_irqrmpolicy(&keyboard_hook_id) != 0) return RES_PERMISSION_ERROR;
    return RES_OK;
}

/**
 * @brief Restores the keyboard controller to its default state.
 * @return Result indicating success or specific error.
 */
Result(kbc_restore)() {
    uint8_t commandWord;

    if (sys_outb(KBC_STATUS_REG, KBC_READ_CMD_BYTE) != RES_OK) return RES_IO_ERROR;
    if (res_util_sys_inb(KBC_OUT_BUF, &commandWord) != RES_OK) return RES_IO_ERROR;

    // Make sure interrupts are enabled
    commandWord |= BIT(0);

    if (sys_outb(KBC_STATUS_REG, 0X60) != RES_OK) return RES_IO_ERROR;
    if (sys_outb(0x60, commandWord) != RES_OK) return RES_IO_ERROR;
    return RES_OK;
}
