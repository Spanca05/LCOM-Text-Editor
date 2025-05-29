#include "logic_tempname.h"

int esc_counter = 0;

// values just to test the update_cursor, these should be defined with the graphics part
int min_y = 0;
int min_x = 0;
int max_y = 64;
int max_x = 64;

//just to test buffer logic
int buffer_count = 1;

Result(scancode_to_character)(uint16_t scancode, Character *character) {
    if (character == NULL) return RES_INVALID_ARGUMENT;

    switch (scancode) {
    // 0x01
    case 0x01:
        *character = CHAR_ESC;
        break; // Esc

    // 0x02 - 0x0B: Numbers row (with Shift/AltGr for symbols)
    case 0x02: *character = CHAR_1; break; // '1' (Shift: '!')
    case 0x03: *character = CHAR_2; break; // '2' (Shift: '"', AltGr: '@')
    case 0x04: *character = CHAR_3; break; // '3' (Shift: '#', AltGr: '£')
    case 0x05: *character = CHAR_4; break; // '4' (Shift: '$', AltGr: '§')
    case 0x06: *character = CHAR_5; break; // '5' (Shift: '%', AltGr: '€')
    case 0x07: *character = CHAR_6; break; // '6' (Shift: '&')
    case 0x08: *character = CHAR_7; break; // '7' (Shift: '/', AltGr: '{')
    case 0x09: *character = CHAR_8; break; // '8' (Shift: '(', AltGr: '[')
    case 0x0A: *character = CHAR_9; break; // '9' (Shift: ')', AltGr: ']')
    case 0x0B:
        *character = CHAR_0;
        break;                             // '0' (Shift: '=', AltGr: '}')

    // 0x0C - 0x0D: Apostrophe and Plus
    case 0x0C: *character = CHAR_APOSTROPHE; break; // '\'' (Shift: '?')
    case 0x0D:
        *character = CHAR_PLUS;
        break;                                      // '«' (Shift: '»')

    // 0x0E - 0x0F: Backspace and Tab
    case 0x0E: *character = CHAR_BACKSPACE; break; // Backspace '\b'
    case 0x0F:
        *character = CHAR_TAB;
        break;                                     // Tab '\t'

    // 0x10 - 0x19: QWERTYUIOP
    case 0x10: *character = CHAR_q; break; // 'q'
    case 0x11: *character = CHAR_w; break; // 'w'
    case 0x12: *character = CHAR_e; break; // 'e'
    case 0x13: *character = CHAR_r; break; // 'r'
    case 0x14: *character = CHAR_t; break; // 't'
    case 0x15: *character = CHAR_y; break; // 'y'
    case 0x16: *character = CHAR_u; break; // 'u'
    case 0x17: *character = CHAR_i; break; // 'i'
    case 0x18: *character = CHAR_o; break; // 'o'
    case 0x19:
        *character = CHAR_p;
        break;                             // 'p'

    // 0x1A - 0x1B: Plus and Acute
    case 0x1A: *character = CHAR_PLUS; break; // '+' (Shift: '*')
    case 0x1B:
        *character = CHAR_ACUTE;
        break;                                // '´' (Shift: '`')

    // 0x1C: Enter
    case 0x1C:
        *character = CHAR_ENTER;
        break; // Enter

    // 0x1D: Left Ctrl
    case 0x1D:
        *character = CHAR_LCTRL;
        break; // Left Ctrl

    // 0x1E - 0x28: ASDFGHJKLÇº
    case 0x1E: *character = CHAR_a; break;       // 'a'
    case 0x1F: *character = CHAR_s; break;       // 's'
    case 0x20: *character = CHAR_d; break;       // 'd'
    case 0x21: *character = CHAR_f; break;       // 'f'
    case 0x22: *character = CHAR_g; break;       // 'g'
    case 0x23: *character = CHAR_h; break;       // 'h'
    case 0x24: *character = CHAR_j; break;       // 'j'
    case 0x25: *character = CHAR_k; break;       // 'k'
    case 0x26: *character = CHAR_l; break;       // 'l'
    case 0x27: *character = CHAR_CEDILLA; break; // 'ç'
    case 0x28:
        *character = CHAR_MOI;
        break;                                   // 'º' (Shift: 'ª')

    // 0x29: Backslash
    case 0x29:
        *character = CHAR_BACKSLASH;
        break; // '\' (Shift: '|')

    // 0x2A: Left Shift
    case 0x2A:
        *character = CHAR_LSHIFT;
        break; // Left Shift

    // 0x2B: Tilde
    case 0x2B:
        *character = CHAR_TILDE;
        break; // '~' (Shift: '^')

    // 0x2C - 0x32: ZXCVBNM,.-
    case 0x2C: *character = CHAR_z; break;     // 'z'
    case 0x2D: *character = CHAR_x; break;     // 'x'
    case 0x2E: *character = CHAR_c; break;     // 'c'
    case 0x2F: *character = CHAR_v; break;     // 'v'
    case 0x30: *character = CHAR_b; break;     // 'b'
    case 0x31: *character = CHAR_n; break;     // 'n'
    case 0x32: *character = CHAR_m; break;     // 'm'
    case 0x33: *character = CHAR_COMMA; break; // ',' (Shift: ';')
    case 0x34: *character = CHAR_DOT; break;   // '.' (Shift: ':')
    case 0x35:
        *character = CHAR_MINUS;
        break;                                 // '-' (Shift: '_')

    // 0x36: Right Shift
    case 0x36:
        *character = CHAR_RSHIFT;
        break; // Right Shift

    // 0x38: Left Alt
    case 0x38:
        *character = CHAR_LALT;
        break; // Left Alt

    // 0x39: Space
    case 0x39:
        *character = CHAR_SPACE;
        break; // Space

    // 0x3A: Caps Lock
    case 0x3A:
        *character = CHAR_CAPSLOCK;
        break; // Caps Lock

    // 0x56: ISO key (less/greater)
    case 0x56:
        *character = CHAR_LESS;
        break; // '<' (Shift: '>')

    // Extended (E0 prefix)
    case 0xE01D: *character = CHAR_RCTRL; break;       // Right Ctrl (Note: for me (leo) is useless because of minix)
    case 0xE038: *character = CHAR_RALT; break;        // Right Alt (AltGr)
    case 0xE048: *character = CHAR_ARROW_UP; break;    // Up Arrow
    case 0xE04B: *character = CHAR_ARROW_LEFT; break;  // Left Arrow
    case 0xE04D: *character = CHAR_ARROW_RIGHT; break; // Right Arrow
    case 0xE050:
        *character = CHAR_ARROW_DOWN;
        break;                                         // Down Arrow

        /* //!Not used for now
        // 0x37: Keypad *
        case 0x37: *character = CHAR_NUMPAD_ASTERISK; break; // Keypad '*'
        // 0x3B - 0x44: F1-F10
        case 0x3B: *character = CHAR_F1; break;
        case 0x3C: *character = CHAR_F2; break;
        case 0x3D: *character = CHAR_F3; break;
        case 0x3E: *character = CHAR_F4; break;
        case 0x3F: *character = CHAR_F5; break;
        case 0x40: *character = CHAR_F6; break;
        case 0x41: *character = CHAR_F7; break;
        case 0x42: *character = CHAR_F8; break;
        case 0x43: *character = CHAR_F9; break;
        case 0x44: *character = CHAR_F10; break;
        // 0x47 - 0x53: Keypad 7-1, 8-2, 9-3, -, 4, 5, 6, +, 1, 2, 3, 0, .
        case 0x47: *character = CHAR_NUMPAD_7; break;
        case 0x48: *character = CHAR_NUMPAD_8; break;
        case 0x49: *character = CHAR_NUMPAD_9; break;
        case 0x4A: *character = CHAR_NUMPAD_MINUS; break;
        case 0x4B: *character = CHAR_NUMPAD_4; break;
        case 0x4C: *character = CHAR_NUMPAD_5; break;
        case 0x4D: *character = CHAR_NUMPAD_6; break;
        case 0x4E: *character = CHAR_NUMPAD_PLUS; break;
        case 0x4F: *character = CHAR_NUMPAD_1; break;
        case 0x50: *character = CHAR_NUMPAD_2; break;
        case 0x51: *character = CHAR_NUMPAD_3; break;
        case 0x52: *character = CHAR_NUMPAD_0; break;
        case 0x53: *character = CHAR_NUMPAD_DOT; break;
        // 0x57 - 0x58: F11-F12
        case 0x57: *character = CHAR_F11; break;
        case 0x58: *character = CHAR_F12; break;
        case 0xE01C: *character = CHAR_NUMPAD_ENTER; break; // Keypad Enter
        case 0xE035: *character = CHAR_NUMPAD_DIVIDE; break;// Keypad '/'
        case 0xE047: *character = CHAR_HOME; break;         // Home
        case 0xE049: *character = CHAR_PAGEUP; break;       // Page Up
        case 0xE04F: *character = CHAR_END; break;          // End
        case 0xE051: *character = CHAR_PAGEDOWN; break;     // Page Down
        case 0xE052: *character = CHAR_INSERT; break;       // Insert
        case 0xE053: *character = CHAR_DELETE; break;       // Delete*/

    default: return RES_INVALID_ARGUMENT; // Unrecognized scancode
    }

    return RES_OK;
}

Result(character_handler)(char *buffer, int buffer_size, Character *character, Cursor *cursor, KBD_modifier *kbd_modifier) {
    if (character == NULL) return RES_INVALID_ARGUMENT;

    if (*character == CHAR_ESC) {
        printf("ESC was pressed");
        if (esc_counter == 0) update_cursor(cursor, *character);
    }

    else if (is_drawable(*character)) {
        cursor->visible = true;
        if ((has_ralt(*character) && kbd_modifier->ralt)
            || (has_shift(*character) && (kbd_modifier->shift || kbd_modifier->caps_lock)))
            modify_character(*kbd_modifier, character);

        insert_into_buffer(buffer, buffer_size, &buffer_count, *character);
        printf("Buffer: %s\nChar: %s\n",buffer,(char *)character_to_char_map[*character]);
    }

    else if (is_arrow(*character)) {
        cursor->visible = true;
        update_cursor(cursor, *character);
        printf("This is an arrow\n");
    }

    else if (is_kbd_modifier(*character)) {
        cursor->visible = true;
        press_kbd_modifier(kbd_modifier, *character);
        printf("This is a press kbd_modifier\n");
    }

    else
        return RES_ERROR;

    return RES_OK;
}

bool is_drawable(Character character) {
    switch (character) {
    // Non-drawable or control keys
    case CHAR_NONE:
    case CHAR_ESC:
    case CHAR_ARROW_UP:
    case CHAR_ARROW_DOWN:
    case CHAR_ARROW_LEFT:
    case CHAR_ARROW_RIGHT:
    case CHAR_LSHIFT:
    case CHAR_RSHIFT:
    case CHAR_LCTRL:
    case CHAR_RCTRL:
    case CHAR_LALT:
    case CHAR_RALT:
    case CHAR_CAPSLOCK:
        // Uncomment if you add these keys:
        // case CHAR_LGUI:
        // case CHAR_RGUI:
        // case CHAR_F1: case CHAR_F2: case CHAR_F3: case CHAR_F4: case CHAR_F5:
        // case CHAR_F6: case CHAR_F7: case CHAR_F8: case CHAR_F9: case CHAR_F10:
        // case CHAR_F11: case CHAR_F12:
        return false;
    default: return true;
    }
}

bool is_arrow(Character character) {
    switch (character) {
    case CHAR_ARROW_UP:
    case CHAR_ARROW_DOWN:
    case CHAR_ARROW_LEFT:
    case CHAR_ARROW_RIGHT: return true;

    default: return false;
    }
}

bool is_kbd_modifier(Character character) {
    switch (character) {
    case CHAR_LSHIFT:
    case CHAR_RSHIFT:
    case CHAR_LCTRL:
    case CHAR_RCTRL:
    case CHAR_LALT:
    case CHAR_RALT:
    case CHAR_CAPSLOCK: return true;

    default: return false;
    }
}

bool(has_shift)(Character character) {
    switch (character) {
    case CHAR_a:
    case CHAR_b:
    case CHAR_c:
    case CHAR_d:
    case CHAR_e:
    case CHAR_f:
    case CHAR_g:
    case CHAR_h:
    case CHAR_i:
    case CHAR_j:
    case CHAR_k:
    case CHAR_l:
    case CHAR_m:
    case CHAR_n:
    case CHAR_o:
    case CHAR_p:
    case CHAR_q:
    case CHAR_r:
    case CHAR_s:
    case CHAR_t:
    case CHAR_u:
    case CHAR_v:
    case CHAR_w:
    case CHAR_x:
    case CHAR_y:
    case CHAR_z:
    case CHAR_1:
    case CHAR_2:
    case CHAR_3:
    case CHAR_4:
    case CHAR_5:
    case CHAR_6:
    case CHAR_7:
    case CHAR_8:
    case CHAR_9:
    case CHAR_0:
    case CHAR_BACKSLASH:
    case CHAR_APOSTROPHE:
    case CHAR_LEFT_ANGLE:
    case CHAR_PLUS:
    case CHAR_ACUTE:
    case CHAR_TILDE:
    case CHAR_CEDILLA:
    case CHAR_MOI:
    case CHAR_COMMA:
    case CHAR_DOT:
    case CHAR_MINUS:
    case CHAR_LESS      : return true;
    default             : return false;
    }
}

bool(has_ralt)(Character character) {
    switch (character) {
    case CHAR_2:
    case CHAR_3:
    case CHAR_4:
    case CHAR_5:
    case CHAR_7:
    case CHAR_8:
    case CHAR_9:
    case CHAR_0:
    case CHAR_PLUS:
    case CHAR_ACUTE: return true;
    default        : return false;
    }
}

Result(modify_character)(KBD_modifier kbd_modifier, Character *character) {
    if (character == NULL) return RES_INVALID_ARGUMENT;

    if (kbd_modifier.shift && kbd_modifier.caps_lock) return RES_OK;
    else if (kbd_modifier.shift || kbd_modifier.caps_lock) {
        *character = shift_character_map[*character];
    } else if (kbd_modifier.ralt || (kbd_modifier.lalt && kbd_modifier.ctrl)) {
        *character = ralt_character_map[*character];
    }

    return RES_OK;
}

// Not a good inmplementation, because only allows ASCII, instead of UTF-8
Result(insert_into_buffer)(char *buffer, int buffer_size, int *pos, Character character) {
    if (buffer == NULL || *pos < 0 || *pos > buffer_size) return RES_INVALID_ARGUMENT;

    int char_size = 1;
    size_t len = strlen(buffer);
    char const *c = character_to_char_map[character];

    if (character_size(c, &char_size) != RES_OK) return RES_ERROR;
    
    memmove(buffer + *pos + char_size, buffer + *pos, len - *pos + 1);
    memcpy(buffer + *pos, c, char_size);
    *pos += char_size;

    return RES_OK;
}

Result(update_cursor)(Cursor *cursor, Character character) {
    if (cursor == NULL) return RES_INVALID_ARGUMENT;

    switch (character) {
    case CHAR_ARROW_UP   : cursor->cy--; break;
    case CHAR_ARROW_DOWN : cursor->cy++; break;
    case CHAR_ARROW_LEFT : cursor->cy--; break;
    case CHAR_ARROW_RIGHT: cursor->cx++; break;
    case CHAR_ESC        : cursor->visible = false; return RES_OK;

    default: return RES_INVALID_ARGUMENT;
    }

    if (cursor->cy < min_y) cursor->cy = min_y;
    else if (cursor->cy > max_y) cursor->cy = max_y;

    else if (cursor->cx < min_x) {
        if (cursor->cy == min_y) cursor->cx = min_x;
        else {
            cursor->cx = max_x;
            cursor->cy--;
        }
    } else if (cursor->cx > max_x) {
        if (cursor->cy == max_y) cursor->cx = max_x;
        else {
            cursor->cx = min_x;
            cursor->cy++;
        }
    }

    return RES_OK;
}

Result(press_kbd_modifier)(KBD_modifier *kbd_modifier, Character character) {
    if (kbd_modifier == NULL) return RES_INVALID_ARGUMENT;

    switch (character) {
    case CHAR_CAPSLOCK:
        kbd_modifier->caps_lock = !kbd_modifier->caps_lock;
        break; // If you keep the shift pressed it keep flipping is value, should be constant, Another issue: If you do the timing right, it also changes the logic fh 
    case CHAR_LSHIFT:
    case CHAR_RSHIFT: kbd_modifier->shift = true; break;
    case CHAR_LCTRL :
    case CHAR_RCTRL : kbd_modifier->ctrl = true; break;
    case CHAR_LALT  : kbd_modifier->lalt = true; break;
    case CHAR_RALT  : kbd_modifier->ralt = true; break;

    default: return RES_INVALID_ARGUMENT;
    }

    return RES_OK;
}

Result(release_handler)(Character *character, Cursor *cursor, KBD_modifier *kbd_modifier, bool *running) {
    if (character == NULL) return RES_INVALID_ARGUMENT;

    if (*character == CHAR_ESC) {
        printf("ESC was released");
        if (esc_counter == 0) esc_counter++;

        else if (esc_counter == 1) *running = false;
    } else if (is_kbd_modifier(*character)) {
        printf("This is a release kbd_modifier\n");
        esc_counter--;
        release_kbd_modifier(kbd_modifier, *character);
    } else esc_counter--;

    if (esc_counter < 0) esc_counter = 0;

    return RES_OK;
}

Result(release_kbd_modifier)(KBD_modifier *kbd_modifier, Character character) {
    if (kbd_modifier == NULL) return RES_INVALID_ARGUMENT;

    switch (character) {
    case CHAR_CAPSLOCK: return RES_OK;
    case CHAR_LSHIFT  :
    case CHAR_RSHIFT  : kbd_modifier->shift = false; break;
    case CHAR_LCTRL   :
    case CHAR_RCTRL   : kbd_modifier->ctrl = false; break;
    case CHAR_LALT    : kbd_modifier->ralt = false; break;
    case CHAR_RALT    : kbd_modifier->lalt = false; break;

    default: return RES_INVALID_ARGUMENT;
    }

    return RES_OK;
}

Result(character_size)(char const *char_, int *len) { //The number of bytes correspondes to the bytes that the Character occupies (All because of UTF-8 characters...)
    if (char_ == NULL || len == NULL) return RES_INVALID_ARGUMENT;
    
    unsigned char c = *char_;
    if ((c & 0xE0) == 0xC0) *len = 2; // 2 bytes
    else if ((c & 0xF0) == 0xE0) *len = 3; // 3 bytes
    else if ((c & 0xF8) == 0xF0) *len = 4; // 4 bytes
    else *len = 1;

    return RES_OK;
}
