
#ifndef DRIVER_MANAGEMENT_H
#define DRIVER_MANAGEMENT_H

#include <stdint.h>

void setup_graphics();

void subscribe_to_devices(uint8_t *timer_bit, uint8_t *kbd_bit);

void drivers_cleanup();

#endif // DRIVER_MANAGEMENT_H
