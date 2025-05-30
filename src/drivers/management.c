#include <stdint.h>

#include "../utils/result.h"
#include "VBE.h"
#include "graphics.h"
#include "keyboard.h"
#include "management.h"
#include "timer.h"

void setup_graphics() {
    // Set graphics mode and map video memory
    if (set_graphic_mode(VBE_1024P_DC) != RES_OK) {
        fprintf(stderr, "Failed to set graphics mode\n");
        drivers_cleanup();
        exit(EXIT_FAILURE);
    }

    if (res_vg_init(VBE_1024P_DC) != RES_OK) {
        fprintf(stderr, "Failed to map video memory\n");
        drivers_cleanup();
        exit(EXIT_FAILURE);
    }

    // Initialize back buffer
    if (init_backbuffer() != RES_OK) {
        fprintf(stderr, "Failed to initialize back buffer\n");
        drivers_cleanup();
        exit(EXIT_FAILURE);
    }
}

void subscribe_to_devices(uint8_t *timer_bit, uint8_t *kbd_bit) {
    // Subscribe timer interrupts
    if (res_timer_subscribe_int(timer_bit) != RES_OK) {
        fprintf(stderr, "Failed to subscribe timer\n");
        drivers_cleanup();
        exit(EXIT_FAILURE);
    }

    // Subscribe keyboard interrupts
    if (keyboard_subscribe_int(kbd_bit) != RES_OK) {
        fprintf(stderr, "Failed to subscribe keyboard\n");
        drivers_cleanup();
        exit(EXIT_FAILURE);
    }
}

void drivers_cleanup() {
    res_timer_unsubscribe_int();
    keyboard_unsubscribe_int();
    if (set_text_mode() != RES_OK) fprintf(stderr, "Failed to restore text mode\n");
}
