#ifndef _LCOM_MOUSE_H_
#define _LCOM_MOUSE_H_

#include "../utils/result.h"
#include <lcom/lcf.h>


Result(res_mouse_ih)(struct packet *mouse_packet);

/**
 * @brief Subscribes to mouse interrupts.
 * @param bit_no Pointer to store the bit number of the interrupt.
 * @return Result indicating success or specific error.
 */
Result(mouse_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes from mouse interrupts.
 * @return Result indicating success or specific error.
 */
Result(mouse_unsubscribe_int)();

/**
 * @brief Sends a command to the mouse.
 * @param command The command to send.
 * @return Result indicating success or specific error.
 */
Result(mouse_write)(uint8_t command);

#endif
