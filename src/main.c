#include <lcom/lcf.h>
#include <lcom/video_gr.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "drivers/VBE.h"
#include "drivers/graphics.h"
#include "drivers/i8042.h"
#include "drivers/i8254.h"
#include "drivers/kbc.h"
#include "drivers/keyboard.h"
#include "drivers/mouse.h"
#include "drivers/timer.h"
#include "logic_tempname/logic_tempname.h"
#include "utils/character.h"
#include "utils/cursor-rato.h"
#include "utils/kbd_modifier.h"

static uint8_t kbd_bit;
static uint8_t timer_bit;
static void   *video_mem = NULL;
Cursor        *cursor;
KBD_modifier  *kbd_modifier;
const int      buffer_size = 1024;
char          *buffer;

bool handle_keyboard(uint16_t scancode);
void render_screen();

int main(int argc, char *argv[]) {
    // Initialize LCF and Minix framework
    lcf_set_language("EN-US");
    if (lcf_start(argc, argv)) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

void cleanup() {
    res_timer_unsubscribe_int();
    keyboard_unsubscribe_int();
    free(cursor);
    free(kbd_modifier);
    // if (set_text_mode() != RES_OK) fprintf(stderr, "Failed to restore text mode\n");
}

void setup_graphics() {
    // Set graphics mode and map video memory
    if (set_graphic_mode(VBE_1024P_DC) != RES_OK) {
        fprintf(stderr, "Failed to set graphics mode\n");
        cleanup();
        exit(EXIT_FAILURE);
    }

    if (res_vg_init(VBE_1024P_DC, &video_mem) != RES_OK) {
        fprintf(stderr, "Failed to map video memory\n");
        cleanup();
        exit(EXIT_FAILURE);
    }
}

void subscribe_to_devices() {
    // Subscribe timer interrupts
    if (res_timer_subscribe_int(&timer_bit) != RES_OK) {
        fprintf(stderr, "Failed to subscribe timer\n");
        cleanup();
        exit(EXIT_FAILURE);
    }

    // Subscribe keyboard interrupts
    if (keyboard_subscribe_int(&kbd_bit) != RES_OK) {
        fprintf(stderr, "Failed to subscribe keyboard\n");
        cleanup();
        exit(EXIT_FAILURE);
    }
}

void setup_variables() {
    buffer       = malloc(1024);
    *buffer      = '#';
    cursor       = malloc(sizeof(Cursor));
    kbd_modifier = malloc(sizeof(KBD_modifier));
    if (!cursor || !kbd_modifier) {
        fprintf(stderr, "Failed to allocate memory for cursor or kbd_modifier\n");
        exit(EXIT_FAILURE);
    }
    cursor->cx              = 0;
    cursor->cy              = 0;
    cursor->visible         = false;
    kbd_modifier->caps_lock = false;
    kbd_modifier->ctrl      = false;
    kbd_modifier->lalt      = false;
    kbd_modifier->ralt      = false;
    kbd_modifier->shift     = false;
}

// Just to test stuff
void print_variables(Cursor cursor_, KBD_modifier kbd_modifier_) {
    printf("Cursor: cx=%d, cy=%d, vis:%d\n", cursor_.cx, cursor_.cy, cursor_.visible);
    printf(
        "kbd_m: caps=%d, crtl=%d, la=%d, ra=%d, shift=%d\n", kbd_modifier_.caps_lock, kbd_modifier_.ctrl,
        kbd_modifier_.lalt, kbd_modifier_.ralt, kbd_modifier_.shift
    );
}

int(proj_main_loop)(int argc, char *argv[]) {
    // setup_graphics();
    subscribe_to_devices();
    setup_variables();
    bool    running = true;
    int     ipc_status;
    message msg;

    printf("%s\n",buffer);
    // Main event loop
    while (running) {
        if (driver_receive(ANY, &msg, &ipc_status) != OK) continue;
        if (is_ipc_notify(ipc_status) && _ENDPOINT_P(msg.m_source) == HARDWARE) {
            uint32_t irq_set = msg.m_notify.interrupts;

            if (irq_set & timer_bit) {};

            if (irq_set & kbd_bit) {
                uint16_t  scancode;
                Character character;
                if (keyboard_ih(&scancode) != RES_OK) continue; // needs to be changed

                if (!(scancode & BIT(7)))                       // makecode part
                {
                    if (scancode_to_character(scancode, &character) != RES_OK) printf("Couldn't convert scancode!\n");
                    if (character_handler(buffer, buffer_size, &character, cursor, kbd_modifier) != RES_OK)
                        printf("Something wrong!\n");
                } else // breakcode part
                {
                    if (scancode_to_character(scancode - 128, &character) != RES_OK)
                        printf("Couldn't convert scancode!\n");
                    if (release_handler(&character, cursor, kbd_modifier, &running) != RES_OK)
                        printf("Something wrong!\n");
                }
            }
        }
        // render_screen();
    }

    // Cleanup and restore text mode
    cleanup();
    return 0;
}

void render_screen() {
    // Clear screen to light grey
    res_vg_draw_rectangle(0, 0, mode_info.XResolution, mode_info.YResolution, 0xCCCCCC);
    // TODO: draw text buffer and cursor here using vg_draw_pixel or custom font routines
}
