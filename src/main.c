#include <lcom/lcf.h>
#include <minix/drivers.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "drivers/graphics.h"
#include "drivers/keyboard.h"
#include "drivers/management.h"
#include "graphics/buffer_renderer.h"
#include "graphics/font16x32.h"
#include "graphics/text_renderer.h"
#include "model/buffer.h"
#include "model/character.h"
#include "model/key.h"
#include "model/modifiers.h"
#include "utils/result.h"
#include "model/directory.h"

// Files directory path and menu buffer
const char *FILES_DIRECTORY = "./src/Files";
char menu_buffer[2048];
char* filenames[2048];
int num_files = 0;

// Function definitions
void        handle_timer_interrupts();
void        handle_keyboard_interrupt();
void        render_screen();
static void render_header(uint16_t header_height);
static void render_footer(uint16_t header_height);


// Drivers Info
static uint8_t timer_bit;
static uint8_t kbd_bit;

// Text Editor State
static Modifiers modifiers;
static bool      running;

// LCF Setup
int main(int argc, char *argv[]) {
    // Initialize LCF and Minix framework
    lcf_set_language("EN-US");
    lcf_start(argc, argv);
    lcf_cleanup();
    return EXIT_SUCCESS;
}

// Program Loop
int(proj_main_loop)(int argc, char *argv[]) {
    // Init drivers
    setup_graphics();
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
    running = true;
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

            // Redraw the screen
            render_screen();
        }
    }

    // Cleanup and restore text mode
    drivers_cleanup();
    return RES_OK;
}

/**
 * Handles timer interrupts by updating the cursor state.
 */
void handle_timer_interrupts() {
    buffer_clock_tick();
    // TODO Handle timer interrupts
}

/**
 * Handles keyboard interrupts by processing key inputs and updating the buffer or cursor state.
 */
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

    // Handle ctrl key-binds
    if (modifiers.ctrl) {
        switch (key) {
        case KEY_BACKSPACE:
            if (isPressCode) backspace_word_from_buffer();
            return;
        case KEY_DELETE:
            if (isPressCode) delete_word_from_buffer();
            return;
        default: break;
        }
    }

    // Handle left alt key-binds
    if (modifiers.lalt) return; // TODO Implement Left ALT key-binds


    // Handle non-printable (non-text) keys
    if (!key_is_printable(key)) {
        switch (key) {
        case KEY_ESC:
            if (!isPressCode) running = false;
            break;
        case KEY_CAPSLOCK:
            if (!isPressCode) modifiers.caps_lock ^= 1;
            break;
        case KEY_BACKSPACE:
            if (isPressCode) backspace_character_from_buffer();
            break;
        case KEY_DELETE:
            if (isPressCode) delete_character_from_buffer();
            break;
        case KEY_ENTER:
            if (isPressCode) add_new_line_to_buffer();
            break;

        case KEY_LCTRL:
        case KEY_RCTRL: modifiers.ctrl = isPressCode; break;

        case KEY_LSHIFT:
        case KEY_RSHIFT: modifiers.shift = isPressCode; break;

        case KEY_LALT: modifiers.lalt = isPressCode; break;
        case KEY_RALT: modifiers.ralt = isPressCode; break;

        case KEY_ARROW_UP:
            if (isPressCode) move_cursor_up();
            break;
        case KEY_ARROW_DOWN:
            if (isPressCode) move_cursor_down();
            break;
        case KEY_ARROW_LEFT:
            if (isPressCode) move_cursor_left();
            break;
        case KEY_ARROW_RIGHT:
            if (isPressCode) move_cursor_right();
            break;
        default: break;
        }

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

    // If a text modifier exists and was not used
    // Add it to the buffer
    if (modifiers.textModifier != TEXT_MOD_NONE && !textModifierUsed)
        add_character_to_buffer(text_modifier_to_character(modifiers.textModifier));

    // If a text modifier exits and the key was a space
    // Add only the text modifier to the buffer
    if (modifiers.textModifier != TEXT_MOD_NONE && character == CHAR_SPACE) return;

    // Clear the text modifier
    modifiers.textModifier = TEXT_MOD_NONE;

    // Add character to the buffer
    add_character_to_buffer(character);
}

/**
 * Renders the main screen of the text editor, including the header, footer, and text buffer.
 */
void render_screen() {
    // Clear screen to grey
    res_vg_draw_rectangle(0, 0, mode_info.XResolution, mode_info.YResolution, 0x272A32);

    // Header and footer heights
    uint16_t header_height = FONT_HEIGHT + 4;

    // Draw header and footer
    render_header(header_height);
    render_footer(header_height);

    // Draw text buffer contents below header
    render_buffer(header_height);

    // Swap buffers
    swap_buffers();
}

/**
 * Renders the header of the text editor window.
 *
 * @param header_height The height of the header.
 */
static void render_header(uint16_t header_height) {
    uint32_t header_bg = 0x171A22;
    // Background
    res_vg_draw_rectangle(0, 0, mode_info.XResolution, header_height, header_bg);

    // Text "File" on left, 'X' on right
    uint16_t  text_y        = (header_height - FONT_HEIGHT) / 2;
    Character file_string[] = { CHAR_F, CHAR_i, CHAR_l, CHAR_e };

    draw_string(5, text_y, 0xFFFFFF, file_string, 4);
    res_vg_draw_rectangle(mode_info.XResolution - FONT_WIDTH * 2, 0, FONT_WIDTH * 2, header_height, 0xDD1F1F);
    draw_character(mode_info.XResolution - FONT_WIDTH * 1.5, text_y, CHAR_X, 0xFFFFFF);
}

/**
 * Renders the footer of the text editor window.
 *
 * @param header_height The height of the header, used to calculate the footer position.
 */
static void render_footer(uint16_t header_height) {
    uint32_t footer_bg = 0x171A22;
    uint16_t y0        = mode_info.YResolution - header_height;
    res_vg_draw_rectangle(0, y0, mode_info.XResolution, header_height, footer_bg);

    // Draw cursor position (Ln, Col) on the left side
    uint16_t text_y = y0 + (header_height - FONT_HEIGHT) / 2;
    char     footer_text_string[32];
    snprintf(
        footer_text_string, sizeof(footer_text_string), "Ln %llu, Col %llu", text_buffer.cursor.line,
        text_buffer.cursor.column
    );

    Character *footer_text_characters;
    uint64_t   footer_text_length = strlen(footer_text_string);
    if (string_to_characters(footer_text_string, footer_text_length, &footer_text_characters) == RES_OK) {
        draw_string(5, text_y, 0xFFFFFF, footer_text_characters, footer_text_length);
        free(footer_text_characters);
    }
}

void render_menu(char *path, char *buffer, char *filenames[], int *num_files) {
    if (path == NULL || buffer == NULL || filenames == NULL) return RES_INVALID_ARGUMENT;

    render_directory(path, filenames, num_files);
    return RES_OK;
}
