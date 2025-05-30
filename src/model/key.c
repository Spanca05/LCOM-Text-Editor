#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "../utils/result.h"
#include "../utils/utils.h"
#include "key.h"

Result scancode_to_key(uint16_t scancode, Key *key, bool *isPressCode) {
    if (key == NULL) return RES_INVALID_ARGUMENT;
    if (isPressCode == NULL) return RES_INVALID_ARGUMENT;

    switch (scancode) {
    case 0x00: *key = KEY_NONE; break;


    case 0x1E:
    case 0x9E: *key = KEY_a; break;
    case 0x30:
    case 0xB0: *key = KEY_b; break;
    case 0x2E:
    case 0xAE: *key = KEY_c; break;
    case 0x20:
    case 0xA0: *key = KEY_d; break;
    case 0x12:
    case 0x92: *key = KEY_e; break;
    case 0x21:
    case 0xA1: *key = KEY_f; break;
    case 0x22:
    case 0xA2: *key = KEY_g; break;
    case 0x23:
    case 0xA3: *key = KEY_h; break;
    case 0x17:
    case 0x97: *key = KEY_i; break;
    case 0x24:
    case 0xA4: *key = KEY_j; break;
    case 0x25:
    case 0xA5: *key = KEY_k; break;
    case 0x26:
    case 0xA6: *key = KEY_l; break;
    case 0x32:
    case 0xB2: *key = KEY_m; break;
    case 0x31:
    case 0xB1: *key = KEY_n; break;
    case 0x18:
    case 0x98: *key = KEY_o; break;
    case 0x19:
    case 0x99: *key = KEY_p; break;
    case 0x10:
    case 0x90: *key = KEY_q; break;
    case 0x13:
    case 0x93: *key = KEY_r; break;
    case 0x1F:
    case 0x9F: *key = KEY_s; break;
    case 0x14:
    case 0x94: *key = KEY_t; break;
    case 0x16:
    case 0x96: *key = KEY_u; break;
    case 0x2F:
    case 0xAF: *key = KEY_v; break;
    case 0x11:
    case 0x91: *key = KEY_w; break;
    case 0x2D:
    case 0xAD: *key = KEY_x; break;
    case 0x15:
    case 0x95: *key = KEY_y; break;
    case 0x2C:
    case 0xAC: *key = KEY_z; break;
    case 0x27:
    case 0xA7: *key = KEY_CEDILLA; break;
    case 0x28:
    case 0xA8: *key = KEY_ORDINAL; break;


    case 0x02:
    case 0x82: *key = KEY_1; break;
    case 0x03:
    case 0x83: *key = KEY_2; break;
    case 0x04:
    case 0x84: *key = KEY_3; break;
    case 0x05:
    case 0x85: *key = KEY_4; break;
    case 0x06:
    case 0x86: *key = KEY_5; break;
    case 0x07:
    case 0x87: *key = KEY_6; break;
    case 0x08:
    case 0x88: *key = KEY_7; break;
    case 0x09:
    case 0x89: *key = KEY_8; break;
    case 0x0A:
    case 0x8A: *key = KEY_9; break;
    case 0x0B:
    case 0x8B: *key = KEY_0; break;


    case 0x3B:
    case 0xBB: *key = KEY_F1; break;
    case 0x3C:
    case 0xBC: *key = KEY_F2; break;
    case 0x3D:
    case 0xBD: *key = KEY_F3; break;
    case 0x3E:
    case 0xBE: *key = KEY_F4; break;
    case 0x3F:
    case 0xBF: *key = KEY_F5; break;
    case 0x40:
    case 0xC0: *key = KEY_F6; break;
    case 0x41:
    case 0xC1: *key = KEY_F7; break;
    case 0x42:
    case 0xC2: *key = KEY_F8; break;
    case 0x43:
    case 0xC3: *key = KEY_F9; break;
    case 0x44:
    case 0xC4: *key = KEY_F10; break;
    case 0x57:
    case 0xD7: *key = KEY_F11; break;
    case 0x58:
    case 0xD8: *key = KEY_F12; break;

    case 0x01:
    case 0x81  : *key = KEY_ESC; break;
    case 0xE052:
    case 0xE0D2: *key = KEY_INSERT; break;
    case 0xE053:
    case 0xE0D3: *key = KEY_DELETE; break;
    case 0x0E  :
    case 0x8E  : *key = KEY_BACKSPACE; break;
    case 0x1C  :
    case 0x9C  : *key = KEY_ENTER; break;
    case 0x0F  :
    case 0x8F  : *key = KEY_TAB; break;
    case 0x39  :
    case 0xB9  : *key = KEY_SPACE; break;


    case 0x29:
    case 0xA9: *key = KEY_BACKSLASH; break;
    case 0x0C:
    case 0x8C: *key = KEY_APOSTROPHE; break;
    case 0x0D:
    case 0x8D: *key = KEY_QUOTE; break;
    case 0x1A:
    case 0x9A: *key = KEY_PLUS; break;
    case 0x1B:
    case 0x9B: *key = KEY_ACCENT; break;
    case 0x2B:
    case 0xAB: *key = KEY_TILL; break;
    case 0x56:
    case 0xD6: *key = KEY_ANGLE; break;
    case 0x33:
    case 0xB3: *key = KEY_COMMA; break;
    case 0x34:
    case 0xB4: *key = KEY_DOT; break;
    case 0x35:
    case 0xB5: *key = KEY_MINUS; break;


    case 0xE048:
    case 0xE0C8: *key = KEY_ARROW_UP; break;
    case 0xE050:
    case 0xE0D0: *key = KEY_ARROW_DOWN; break;
    case 0xE04B:
    case 0xE0CB: *key = KEY_ARROW_LEFT; break;
    case 0xE04D:
    case 0xE0CD: *key = KEY_ARROW_RIGHT; break;

    case 0xE05D:
    case 0xE0DD: *key = KEY_MENU; break;
    case 0xE047:
    case 0xE0C7: *key = KEY_HOME; break;
    case 0xE04F:
    case 0xE0CF: *key = KEY_END; break;
    case 0xE049:
    case 0xE0C9: *key = KEY_PAGEUP; break;
    case 0xE051:
    case 0xE0D1: *key = KEY_PAGEDOWN; break;

    case 0x3A:
    case 0xBA  : *key = KEY_CAPSLOCK; break;
    case 0x2A  :
    case 0xAA  : *key = KEY_LSHIFT; break;
    case 0x36  :
    case 0xB6  : *key = KEY_RSHIFT; break;
    case 0x1D  :
    case 0x9D  : *key = KEY_LCTRL; break;
    case 0xE01D:
    case 0xE09D: *key = KEY_RCTRL; break;
    case 0x38  :
    case 0xB8  : *key = KEY_LALT; break;
    case 0xE038:
    case 0xE0B8: *key = KEY_RALT; break;
    case 0xE05B:
    case 0xE0DB: *key = KEY_LGUI; break;
    case 0xE05C:
    case 0xE0DC: *key = KEY_RGUI; break;

    default: return RES_UNIMPLEMENTED; // Unrecognized scancode
    }

    *isPressCode = (scancode & BIT(7)) == 0;

    return RES_OK;
}

bool key_is_printable(Key key) {
    return
        // Alphabet keys
        (key >= KEY_a && key <= KEY_ORDINAL) ||

        // Number keys
        (key >= KEY_1 && key <= KEY_0) ||

        // Other printable keys
        (key >= KEY_TAB && key <= KEY_MINUS);
}

const char *key_names[] = {
    [KEY_NONE]        = "KEY_NONE",
    [KEY_a]           = "KEY_a",
    [KEY_b]           = "KEY_b",
    [KEY_c]           = "KEY_c",
    [KEY_d]           = "KEY_d",
    [KEY_e]           = "KEY_e",
    [KEY_f]           = "KEY_f",
    [KEY_g]           = "KEY_g",
    [KEY_h]           = "KEY_h",
    [KEY_i]           = "KEY_i",
    [KEY_j]           = "KEY_j",
    [KEY_k]           = "KEY_k",
    [KEY_l]           = "KEY_l",
    [KEY_m]           = "KEY_m",
    [KEY_n]           = "KEY_n",
    [KEY_o]           = "KEY_o",
    [KEY_p]           = "KEY_p",
    [KEY_q]           = "KEY_q",
    [KEY_r]           = "KEY_r",
    [KEY_s]           = "KEY_s",
    [KEY_t]           = "KEY_t",
    [KEY_u]           = "KEY_u",
    [KEY_v]           = "KEY_v",
    [KEY_w]           = "KEY_w",
    [KEY_x]           = "KEY_x",
    [KEY_y]           = "KEY_y",
    [KEY_z]           = "KEY_z",
    [KEY_CEDILLA]     = "KEY_CEDILLA",
    [KEY_ORDINAL]     = "KEY_ORDINAL",
    [KEY_1]           = "KEY_1",
    [KEY_2]           = "KEY_2",
    [KEY_3]           = "KEY_3",
    [KEY_4]           = "KEY_4",
    [KEY_5]           = "KEY_5",
    [KEY_6]           = "KEY_6",
    [KEY_7]           = "KEY_7",
    [KEY_8]           = "KEY_8",
    [KEY_9]           = "KEY_9",
    [KEY_0]           = "KEY_0",
    [KEY_F1]          = "KEY_F1",
    [KEY_F2]          = "KEY_F2",
    [KEY_F3]          = "KEY_F3",
    [KEY_F4]          = "KEY_F4",
    [KEY_F5]          = "KEY_F5",
    [KEY_F6]          = "KEY_F6",
    [KEY_F7]          = "KEY_F7",
    [KEY_F8]          = "KEY_F8",
    [KEY_F9]          = "KEY_F9",
    [KEY_F10]         = "KEY_F10",
    [KEY_F11]         = "KEY_F11",
    [KEY_F12]         = "KEY_F12",
    [KEY_ESC]         = "KEY_ESC",
    [KEY_INSERT]      = "KEY_INSERT",
    [KEY_DELETE]      = "KEY_DELETE",
    [KEY_BACKSPACE]   = "KEY_BACKSPACE",
    [KEY_ENTER]       = "KEY_ENTER",
    [KEY_TAB]         = "KEY_TAB",
    [KEY_SPACE]       = "KEY_SPACE",
    [KEY_BACKSLASH]   = "KEY_BACKSLASH",
    [KEY_APOSTROPHE]  = "KEY_APOSTROPHE",
    [KEY_QUOTE]       = "KEY_QUOTE",
    [KEY_PLUS]        = "KEY_PLUS",
    [KEY_ACCENT]      = "KEY_ACCENT",
    [KEY_TILL]        = "KEY_TILL",
    [KEY_ANGLE]       = "KEY_ANGLE",
    [KEY_COMMA]       = "KEY_COMMA",
    [KEY_DOT]         = "KEY_DOT",
    [KEY_MINUS]       = "KEY_MINUS",
    [KEY_ARROW_UP]    = "KEY_ARROW_UP",
    [KEY_ARROW_DOWN]  = "KEY_ARROW_DOWN",
    [KEY_ARROW_LEFT]  = "KEY_ARROW_LEFT",
    [KEY_ARROW_RIGHT] = "KEY_ARROW_RIGHT",
    [KEY_MENU]        = "KEY_MENU",
    [KEY_HOME]        = "KEY_HOME",
    [KEY_END]         = "KEY_END",
    [KEY_PAGEUP]      = "KEY_PAGEUP",
    [KEY_PAGEDOWN]    = "KEY_PAGEDOWN",
    [KEY_CAPSLOCK]    = "KEY_CAPSLOCK",
    [KEY_LSHIFT]      = "KEY_LSHIFT",
    [KEY_RSHIFT]      = "KEY_RSHIFT",
    [KEY_LCTRL]       = "KEY_LCTRL",
    [KEY_RCTRL]       = "KEY_RCTRL",
    [KEY_LALT]        = "KEY_LALT",
    [KEY_RALT]        = "KEY_RALT",
    [KEY_LGUI]        = "KEY_LGUI",
    [KEY_RGUI]        = "KEY_RGUI",
};
