#ifndef DRIVER_MANAGEMENT_H
#define DRIVER_MANAGEMENT_H

#include <stdint.h>

/**
 * @brief Sets up the graphics mode and initializes the video memory and back buffer.
 *
 * Exits the program if any of the initialization steps fail.
 */
void setup_graphics();

/**
 * @brief Subscribes to timer and keyboard interrupts.
 *
 * @param timer_bit Pointer to store the timer interrupt bitmask.
 * @param kbd_bit Pointer to store the keyboard interrupt bitmask.
 *
 * Exits the program if subscription fails.
 */
void subscribe_to_devices(uint8_t *timer_bit, uint8_t *kbd_bit);

/**
 * @brief Cleans up the drivers by unsubscribing interrupts and restoring text mode.
 */
void drivers_cleanup();

#endif // DRIVER_MANAGEMENT_H
