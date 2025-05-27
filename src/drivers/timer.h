#ifndef _DEVICE_DRIVERS_TIMER_H_
#define _DEVICE_DRIVERS_TIMER_H_

#include "../utils/result.h"
#include <stdint.h>

/**
 * @brief Sets the frequency of the specified timer.
 * @param timer The timer to configure (0, 1, or 2).
 * @param freq The desired frequency.
 * @return Result indicating success or specific error.
 */
Result(res_timer_set_frequency)(uint8_t timer, uint32_t freq);

/**
 * @brief Subscribes to timer interrupts.
 * @param bit_no Pointer to store the interrupt bitmask.
 * @return Result indicating success or specific error.
 */
Result(res_timer_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes from timer interrupts.
 * @return Result indicating success or specific error.
 */
Result(res_timer_unsubscribe_int)();

/**
 * @brief Timer interrupt handler. Increments the global count.
 */
void(timer_int_handler)();

/**
 * @brief Reads the configuration of the specified timer.
 * @param timer The timer to query (0, 1, or 2).
 * @param st Pointer to store the status byte.
 * @return Result indicating success or specific error.
 */
Result(res_timer_get_conf)(uint8_t timer, uint8_t *st);

/**
 * @brief Displays the configuration of the specified timer.
 * @param timer The timer to display.
 * @param st The status byte of the timer.
 * @param field The field to interpret and display.
 * @return Result indicating success or specific error.
 */
Result(res_timer_display_conf)(uint8_t timer, uint8_t st, int field);

#endif // _DEVICE_DRIVERS_TIMER_H_
