#include <lcom/lcf.h>
#include <minix/drivers.h>
#include <stddef.h>
#include <stdint.h>

#include "drivers/keyboard.h"
#include "drivers/management.h"
#include "model/buffer.h"
#include "model/character.h"
#include "model/cursor-rato.h"
#include "model/key.h"
#include "model/modifiers.h"
#include "utils/result.h"

// Function definitions
void handle_timer_interrupts();
void handle_keyboard_interrupt();

// Drivers Info
static uint8_t timer_bit;
static uint8_t kbd_bit;

// Text Editor State
static Modifiers modifiers;
#include "buffer/text_buffer.h"
#include "drivers/VBE.h"
#include "drivers/backbuffer.h"
#include "drivers/graphics.h"
#include "drivers/i8042.h"
#include "drivers/i8254.h"
#include "drivers/keyboard.h"
#include "drivers/timer.h"
#include "graphics/font16x32.h"
#include "graphics/text_renderer.h"

static uint8_t kbd_bit;
// static uint8_t timer_bit;  // no longer using timer for auto-repeat
// static void   *video_mem   = NULL;
static void   *back_buffer = NULL;

static TextBuffer tb; // persistent text buffer

bool handle_keyboard(uint16_t scancode);
void render_screen(void);
void test_text_buffer(void);

// LCF Setup
int main(int argc, char *argv[]) {
    // Initialize LCF and Minix framework
    lcf_set_language("EN-US");
    if (lcf_start(argc, argv)) return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

// Program Loop
void cleanup() {
    keyboard_unsubscribe_int();
    if (set_text_mode() != RES_OK) fprintf(stderr, "Failed to restore text mode\n");
}

void setup_graphics() {
    // Set graphics mode and map video memory
    if (set_graphic_mode(VBE_864P_DC) != RES_OK) {
        fprintf(stderr, "Failed to set graphics mode\n");
        cleanup();
        exit(EXIT_FAILURE);
    }

    if (res_vg_init(VBE_864P_DC, &video_mem) != RES_OK) {
        fprintf(stderr, "Failed to map video memory\n");
        cleanup();
        exit(EXIT_FAILURE);
    }

    // Initialize back buffer
    if (init_backbuffer(&back_buffer) != RES_OK) {
        fprintf(stderr, "Failed to initialize back buffer\n");
        cleanup();
        exit(EXIT_FAILURE);
    }
}

void subscribe_to_devices() {
    // Subscribe keyboard interrupts
    if (keyboard_subscribe_int(&kbd_bit) != RES_OK) {
        fprintf(stderr, "Failed to subscribe keyboard\n");
        cleanup();
        exit(EXIT_FAILURE);
    }
}

int(proj_main_loop)(int argc, char *argv[]) {
    // Init drivers
    // setup_graphics();
    subscribe_to_devices(&timer_bit, &kbd_bit);

    // Init program state
    init_buffer();
    modifiers.caps_lock    = false;
    modifiers.ctrl         = false;
    modifiers.lalt         = false;
    modifiers.ralt         = false;
    modifiers.shift        = false;
    modifiers.textModifier = TEXT_MOD_NONE;


    // Main event loop
    // Initialize text buffer
    if (text_buffer_init(&tb) != RES_OK) {
        fprintf(stderr, "Failed to init text buffer\n");
        cleanup();
        return EXIT_FAILURE;
    }

    // Initial render so the screen is shown before any keypress
    render_screen();

    // Init program state
    init_buffer();
    modifiers.caps_lock    = false;
    modifiers.ctrl         = false;
    modifiers.lalt         = false;
    modifiers.ralt         = false;
    modifiers.shift        = false;
    modifiers.textModifier = TEXT_MOD_NONE;


    // Main event loop
    bool    running = true;
    int     ipc_status;
    message msg;
    while (running) {
        if (driver_receive(ANY, &msg, &ipc_status) != OK) continue;
        if (is_ipc_notify(ipc_status) && _ENDPOINT_P(msg.m_source) == HARDWARE) {
            uint32_t irq_set = msg.m_notify.interrupts;

            // Timer interrupts
            if (irq_set & timer_bit) handle_timer_interrupts();

            // Keyboard interrupts
            if (irq_set & kbd_bit) handle_keyboard_interrupt();
            printf("\033[2J\033[H");
            print_buffer_state(modifiers);
            // Keyboard interrupt: handle key make codes only
            if (irq_set & kbd_bit) {
                uint16_t scancode;
                if (keyboard_ih(&scancode) != RES_OK) continue;
                uint8_t code     = scancode & 0x7F;
                bool    is_break = scancode & 0x0080;

                if (is_break)              // ignore key releases
                    continue;

                if (code == 0x01) {        // ESC make code
                    running = false;
                } else if (code == 0x0E) { // Backspace make code
                    text_buffer_delete_char(&tb);
                } else {                   // Other printable key make
                    text_buffer_insert_char(&tb, (char)code);
                }
            }
        }

        // Clear the screen
        render_screen();
    }


    // Cleanup and restore text mode
    drivers_cleanup();
    return 0;
}

// Timer Interrupt Handler
void handle_timer_interrupts() {
    tick_cursor();
    // TODO Handle timer interrupts
}

// Keyboard Interrupt Handler
void handle_keyboard_interrupt() {
    Result    result;
    uint16_t  scancode;
    Key       key;
    bool      isPressCode;
    Character character;
    bool      textModifierUsed;

    // Handle the keyboard and get the scancode
    if (keyboard_ih(&scancode)) return;

    // Convert the scan code into a Key
    result = scancode_to_key(scancode, &key, &isPressCode);
    if (result == RES_UNIMPLEMENTED) printf("Unimplemented KeyCode: 0x%X\n", scancode);
    if (result != RES_OK) return;

    // Handle non-printable (non-text) keys
    if (!key_is_printable(key)) {
        switch (key) {
        case KEY_CAPSLOCK:
            if (!isPressCode) modifiers.caps_lock ^= 1;
            break;

        case KEY_LCTRL:
        case KEY_RCTRL : modifiers.ctrl = isPressCode; break;
        case KEY_LSHIFT:
        case KEY_RSHIFT: modifiers.shift = isPressCode; break;
        case KEY_LALT  : modifiers.lalt = isPressCode; break;
        case KEY_RALT  : modifiers.ralt = isPressCode; break;

        case KEY_ARROW_UP:
        case KEY_ARROW_DOWN:
        case KEY_ARROW_LEFT:
        case KEY_ARROW_RIGHT:
            if (isPressCode) update_cursor(key);
            break;
        default: break;
        }

        // TODO Implement non printable key code
        return;
    }

    // Handle ctrl key-binds
    if (modifiers.ctrl) {
        // TODO Implement CTRL key-binds
        return;
    }

    // Handle left alt key-binds
    if (modifiers.lalt) {
        // TODO Implement Left ALT key-binds
        return;
    }

    // Map key + modifiers to character
    result = key_to_character(key, modifiers, &character, &textModifierUsed);
    if (result == RES_DOES_NOT_EXIST) return;
    if (result != RES_OK) return;

    // Handle when character is a text modifier
    if (character_is_text_modifier(character)) {
        // Ignore pressing, only releasing is important
        if (isPressCode) return;

        TextModifier newTextModifier = character_to_text_modifier(character);
        // Print and clear if double click
        if (modifiers.textModifier == newTextModifier) {
            add_character_to_buffer(character);
            modifiers.textModifier = TEXT_MOD_NONE;
        }

        // Print old modifier and update
        else {
            Character oldModifier = text_modifier_to_character(modifiers.textModifier);
            if (oldModifier != TEXT_MOD_NONE) add_character_to_buffer(oldModifier);
            modifiers.textModifier = newTextModifier;
        }
        return;
    }

    // Ignore release events
    if (!isPressCode) return;

    // If a text modifier exits and was not used
    // Add it to the buffer and clear it
    if (modifiers.textModifier != TEXT_MOD_NONE && !textModifierUsed) {
        add_character_to_buffer(text_modifier_to_character(modifiers.textModifier));
        modifiers.textModifier = TEXT_MOD_NONE;
    }

    // If a text modifier exits and the key was a space
    // Add only the text modifier to the buffer
    if (modifiers.textModifier != TEXT_MOD_NONE && character == CHAR_SPACE) return;

    // Add character to the buffer
    add_character_to_buffer(character);
}
    // Render the window header (title bar)
    static void render_header(void *buf, uint16_t header_height) {
        uint32_t header_bg = 0x333333;
        // Background
        res_vg_draw_rectangle(buf, 0, 0, mode_info.XResolution, header_height, header_bg);
        // Text "File" on left, 'X' on right
        uint16_t text_y = (header_height - FONT_HEIGHT) / 2;
        draw_string(buf, 5, text_y, "File", 0xFFFFFF);
        draw_character(buf, mode_info.XResolution - FONT_WIDTH - 5, text_y, 23, 0xFF0000);
    }

    // Render the window footer
    static void render_footer(void *buf, uint16_t header_height) {
        uint32_t footer_bg = 0x333333;
        uint16_t y0        = mode_info.YResolution - header_height;
        res_vg_draw_rectangle(buf, 0, y0, mode_info.XResolution, header_height, footer_bg);

        // Draw cursor position (Ln, Col) on the left side
        char pos_text[32];
        snprintf(pos_text, sizeof(pos_text), "Ln %u, Col %u", tb.cursor_row + 1, tb.cursor_col + 1);
        uint16_t text_y = y0 + (header_height - FONT_HEIGHT) / 2;
        draw_string(buf, 5, text_y, pos_text, 0xFFFFFF);
    }

    void render_screen() {
        // Clear screen to grey
        res_vg_draw_rectangle(back_buffer, 0, 0, mode_info.XResolution, mode_info.YResolution, 0xCCCCCC);

        // Header and footer heights
        uint16_t header_height = FONT_HEIGHT + 4;

        // Draw header and footer
        render_header(back_buffer, header_height);
        render_footer(back_buffer, header_height);

        // Draw text buffer contents below header
        text_buffer_render(&tb, back_buffer, header_height);

        // TODO: draw cursor here

        // Swap buffers
        swap_buffers(back_buffer);
    }
