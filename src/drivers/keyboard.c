#include "../utils/result.h"
#include "../utils/utils.h"
#include "i8042.h"
#include <lcom/lcf.h>

// Global variables for keyboard interrupt handling
int  keyboard_hook_id = 1;
bool complete_scan    = true; // Flag to indicate that we are waiting for the second byte

Result(keyboard_ih)(uint16_t *scancode) {
    uint8_t status, byte;

    // Read status register
    if (res_util_sys_inb(KBC_STATUS_REG, &status) != RES_OK) return RES_IO_ERROR;

    // Check if there was some communication error
    if (PARITY_ERROR(status)) return RES_IO_ERROR;
    if (TIMEOUT_ERROR(status)) return RES_TIMEOUT;

    // Check if there is no data to be read
    if (!OUTPUT_BUFFER_FULL(status)) return RES_ERROR;

    if (res_util_sys_inb(KBC_OUT_BUF, &byte) != RES_OK) return RES_NOT_READY;

    // Check if scancode is one or two bytes long
    if (byte == 0xE0) {
        complete_scan = false;
        return RES_NOT_READY;
    }

    // If scancode is two bytes long, we combine the values
    if (!complete_scan) {
        complete_scan = true;
        *scancode     = (0xE0 << 8) | byte;
    }

    // Else return the scancode
    else {
        *scancode = (0x00 << 8) | byte;
    }

    return RES_OK;
}

Result(keyboard_subscribe_int)(uint8_t *bit_no) {
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
Result(keyboard_unsubscribe_int)() {
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
