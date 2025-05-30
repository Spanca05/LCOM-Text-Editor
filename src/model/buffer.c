#include <stddef.h>
#include <stdio.h>

#include "../model/cursor-rato.h"
#include "../model/modifiers.h"
#include "buffer.h"

// Buffer State
static char  *buffer;
static Cursor cursor;

// Debug State
// TODO Remove when not needed
static Character latest_written_character;

void init_buffer() {
    buffer = NULL;

    cursor.cx      = 0;
    cursor.cy      = 0;
    cursor.counter = 60;
    cursor.visible = false;

    latest_written_character = CHAR_NONE; // TODO Delete when not needed
}

void tick_cursor() {
    cursor.counter--;
    if (cursor.counter <= 0) {
        cursor.counter  = 60;
        cursor.visible ^= 1;
    }
}

Result update_cursor(Key key) {
    switch (key) {
    case KEY_ARROW_UP   : cursor.cy--; break;
    case KEY_ARROW_DOWN : cursor.cy++; break;
    case KEY_ARROW_LEFT : cursor.cx--; break;
    case KEY_ARROW_RIGHT: cursor.cx++; break;
    case KEY_ESC        : cursor.visible = false; return RES_OK;

    default: return RES_INVALID_ARGUMENT;
    }

    return RES_OK;
}

void add_character_to_buffer(Character character) {
    // TODO Do this properly
    latest_written_character = character;
}

// Debug function
// TODO Remove when not needed
void print_buffer_state(Modifiers modifiers) {
    printf("Cursor: cx=%d, cy=%d, vis:%d\n", cursor.cx, cursor.cy, cursor.visible);
    printf(
        "Modifiers: caps=%d, ctrl=%d, shift=%d, la=%d, ra=%d, text_modifier=%s\n", modifiers.caps_lock, modifiers.ctrl,
        modifiers.shift, modifiers.lalt, modifiers.ralt, text_modifier_names[modifiers.textModifier]
    );

    printf("Latest character: %s\n", character_names[latest_written_character]);
}
