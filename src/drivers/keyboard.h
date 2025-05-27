#ifndef _LCOM_KBD_H_
#define _LCOM_KBD_H_

#include "../utils/result.h"
#include <lcom/lcf.h>


extern uint16_t scancode;

/**
 * @brief Interrupt handler for the Keyboard, updates the global variable scancode.
 *
 * @return Void. The function exits early if any error or invalid state is detected.
 */
void(kbc_ih)();

/**
 * @brief Subscribes to keyboard interrupts.
 * @param bit_no Pointer to store the bit number of the interrupt.
 * @return Result indicating success or specific error.
 */
Result(kbd_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes from keyboard interrupts.
 * @return Result indicating success or specific error.
 */
Result(kbd_unsubscribe_int)();

/**
 * @brief Restores the keyboard controller to its default state.
 * @return Result indicating success or specific error.
 */
Result(kbc_restore)();

#endif
