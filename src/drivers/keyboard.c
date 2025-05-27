#include "../utils/result.h"
#include "../utils/utils.h"
#include "i8042.h"
#include <lcom/lcf.h>

// Global variables for keyboard interrupt handling
int      kbd_hook_id   = 1;
uint16_t scancode      = 0x00;
bool     is_two_byte   = false; // Flag to indicate that we are waiting for the second byte
int      sys_inb_count = 0;

/**
 * @brief Keyboard interrupt handler. Reads scancodes from the keyboard.
 */
void(kbc_ih)() {
    uint8_t status, byte;

    // Read status register
    if (res_util_sys_inb(KBC_STATUS_REG, &status) != RES_OK) return;

    // Check if there was some communication error
    if (status & BIT(7) || status & BIT(6)) return;

    // Check if there is no data to be read
    if (!(status & BIT(0))) return;

    if (res_util_sys_inb(KBC_OUT_BUF, &byte) != RES_OK) return;

    // Check if scancode is one or two bytes long
    if (byte == 0xE0) {
        is_two_byte = true;
        return;
    }

    // If scancode is two bytes long, we combine the values
    if (is_two_byte) {
        scancode    = (0xE0 << 8) | byte;
        is_two_byte = false; // Reset the flag
    } else {
        scancode = byte;
    }
}

/**
 * @brief Subscribes to keyboard interrupts.
 * @param bit_no Pointer to store the bit number of the interrupt.
 * @return Result indicating success or specific error.
 */
Result(kbd_subscribe_int)(uint8_t *bit_no) {
    if (bit_no == NULL) return RES_INVALID_ARGUMENT;

    *bit_no = BIT(kbd_hook_id);

    if (sys_irqsetpolicy(KEYBOARD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &kbd_hook_id) != 0) return RES_PERMISSION_ERROR;

    return RES_OK;
}

/**
 * @brief Unsubscribes from keyboard interrupts.
 * @return Result indicating success or specific error.
 */
Result(kbd_unsubscribe_int)() {
    if (sys_irqrmpolicy(&kbd_hook_id) != 0) return RES_PERMISSION_ERROR;
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

    commandWord |= BIT(0);

    if (sys_outb(KBC_STATUS_REG, 0X60) != RES_OK) return RES_IO_ERROR;

    if (sys_outb(0x60, commandWord) != RES_OK) return RES_IO_ERROR;

    return RES_OK;
}
