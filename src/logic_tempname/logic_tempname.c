#include "logic_tempname.h"

Result(scancode_to_character)(uint16_t scancode, Character *character) {
    if (character == NULL) return RES_INVALID_ARGUMENT;

    switch (scancode) {
        // Letters (lowercase by default)
        case 0x1E: *character = CHAR_a; break; // 'a'
        case 0x30: *character = CHAR_b; break; // 'b'
        case 0x2E: *character = CHAR_c; break; // 'c'
        case 0x20: *character = CHAR_d; break; // 'd'
        case 0x12: *character = CHAR_e; break; // 'e'
        case 0x21: *character = CHAR_f; break; // 'f'
        case 0x22: *character = CHAR_g; break; // 'g'
        case 0x23: *character = CHAR_h; break; // 'h'
        case 0x17: *character = CHAR_i; break; // 'i'
        case 0x24: *character = CHAR_j; break; // 'j'
        case 0x25: *character = CHAR_k; break; // 'k'
        case 0x26: *character = CHAR_l; break; // 'l'
        case 0x32: *character = CHAR_m; break; // 'm'
        case 0x31: *character = CHAR_n; break; // 'n'
        case 0x18: *character = CHAR_o; break; // 'o'
        case 0x19: *character = CHAR_p; break; // 'p'
        case 0x10: *character = CHAR_q; break; // 'q'
        case 0x13: *character = CHAR_r; break; // 'r'
        case 0x1F: *character = CHAR_s; break; // 's'
        case 0x14: *character = CHAR_t; break; // 't'
        case 0x16: *character = CHAR_u; break; // 'u'
        case 0x2F: *character = CHAR_v; break; // 'v'
        case 0x11: *character = CHAR_w; break; // 'w'
        case 0x2D: *character = CHAR_x; break; // 'x'
        case 0x15: *character = CHAR_y; break; // 'y'
        case 0x2C: *character = CHAR_z; break; // 'z'

        // Numbers (top row)
        case 0x02: *character = CHAR_1; break; // '1'
        case 0x03: *character = CHAR_2; break; // '2'
        case 0x04: *character = CHAR_3; break; // '3'
        case 0x05: *character = CHAR_4; break; // '4'
        case 0x06: *character = CHAR_5; break; // '5'
        case 0x07: *character = CHAR_6; break; // '6'
        case 0x08: *character = CHAR_7; break; // '7'
        case 0x09: *character = CHAR_8; break; // '8'
        case 0x0A: *character = CHAR_9; break; // '9'
        case 0x0B: *character = CHAR_0; break; // '0'

        // Symbols and whitespace
        case 0x0C: *character = CHAR_MINUS; break;      // '-'
        case 0x0D: *character = CHAR_EQUAL; break;      // '='
        case 0x1A: *character = CHAR_LBRACKET; break;   // '['
        case 0x1B: *character = CHAR_RBRACKET; break;   // ']'
        case 0x2B: *character = CHAR_BACKSLASH; break;  // '\\'
        case 0x27: *character = CHAR_SEMICOLON; break;  // ';'
        case 0x28: *character = CHAR_APOSTROPHE; break; // '\''
        case 0x29: *character = CHAR_GRAVE; break;      // '`'
        case 0x33: *character = CHAR_COMMA; break;      // ','
        case 0x34: *character = CHAR_DOT; break;        // '.'
        case 0x35: *character = CHAR_SLASH; break;      // '/'
        case 0x39: *character = CHAR_SPACE; break;      // ' '
        case 0x1C: *character = CHAR_ENTER; break;      // '\n'
        case 0x0E: *character = CHAR_BACKSPACE; break;  // '\b'
        case 0x0F: *character = CHAR_TAB; break;        // '\t'
        case 0x01: *character = CHAR_ESC; break;        // ESC

        // Modifier keys
        case 0x2A: *character = CHAR_LSHIFT; break;     // Left Shift (press)
        case 0x36: *character = CHAR_RSHIFT; break;     // Right Shift (press)
        case 0x1D: *character = CHAR_LCTRL; break;      // Left Ctrl (press)
        case 0x38: *character = CHAR_LALT; break;       // Left Alt (press)
        case 0x3A: *character = CHAR_CAPSLOCK; break;   // Caps Lock

        // Arrow keys (extended scancodes)
        case 0xE048: *character = CHAR_ARROW_UP; break;    // Up Arrow
        case 0xE050: *character = CHAR_ARROW_DOWN; break;  // Down Arrow
        case 0xE04B: *character = CHAR_ARROW_LEFT; break;  // Left Arrow
        case 0xE04D: *character = CHAR_ARROW_RIGHT; break; // Right Arrow

        // AltGr/Right Alt (common on international layouts)
        case 0xE038: *character = CHAR_RALT; break;        // Right Alt (AltGr)
        case 0xE01D: *character = CHAR_RCTRL; break;       // Right Ctrl

        default: return RES_INVALID_ARGUMENT; // Unrecognized scancode
    }

    return RES_OK;
}

Result(character_to_caps)(Character *character) {
    if (character == NULL) return RES_INVALID_ARGUMENT;

    // If it's a lowercase letter, convert to uppercase
    if (*character >= CHAR_a && *character <= CHAR_z) {
        *character = (Character)(*character - (CHAR_a - CHAR_A));
        return RES_OK;
    }
    // If not a letter, do nothing
    return RES_INVALID_ARGUMENT;
}

Result(character_from_caps)(Character *character) {
    if (character == NULL) return RES_INVALID_ARGUMENT;

    // If it's an uppercase letter, convert to lowercase
    if (*character >= CHAR_A && *character <= CHAR_Z) {
        *character = (Character)(*character + (CHAR_a - CHAR_A));
        return RES_OK;
    }
    // If not a letter, do nothing
    return RES_INVALID_ARGUMENT;
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

Result(insert_into_buffer)(char *buffer, Character character) { //Not a good inmplementation, because only allows ASCII, instead of UTF-8
    if (buffer == NULL || !is_drawable(character)) return RES_INVALID_ARGUMENT;

    char c = 0;
    switch (character) {
        // Uppercase letters
        case CHAR_A: c = 'A'; break;
        case CHAR_B: c = 'B'; break;
        case CHAR_C: c = 'C'; break;
        case CHAR_D: c = 'D'; break;
        case CHAR_E: c = 'E'; break;
        case CHAR_F: c = 'F'; break;
        case CHAR_G: c = 'G'; break;
        case CHAR_H: c = 'H'; break;
        case CHAR_I: c = 'I'; break;
        case CHAR_J: c = 'J'; break;
        case CHAR_K: c = 'K'; break;
        case CHAR_L: c = 'L'; break;
        case CHAR_M: c = 'M'; break;
        case CHAR_N: c = 'N'; break;
        case CHAR_O: c = 'O'; break;
        case CHAR_P: c = 'P'; break;
        case CHAR_Q: c = 'Q'; break;
        case CHAR_R: c = 'R'; break;
        case CHAR_S: c = 'S'; break;
        case CHAR_T: c = 'T'; break;
        case CHAR_U: c = 'U'; break;
        case CHAR_V: c = 'V'; break;
        case CHAR_W: c = 'W'; break;
        case CHAR_X: c = 'X'; break;
        case CHAR_Y: c = 'Y'; break;
        case CHAR_Z: c = 'Z'; break;

        // Lowercase letters
        case CHAR_a: c = 'a'; break;
        case CHAR_b: c = 'b'; break;
        case CHAR_c: c = 'c'; break;
        case CHAR_d: c = 'd'; break;
        case CHAR_e: c = 'e'; break;
        case CHAR_f: c = 'f'; break;
        case CHAR_g: c = 'g'; break;
        case CHAR_h: c = 'h'; break;
        case CHAR_i: c = 'i'; break;
        case CHAR_j: c = 'j'; break;
        case CHAR_k: c = 'k'; break;
        case CHAR_l: c = 'l'; break;
        case CHAR_m: c = 'm'; break;
        case CHAR_n: c = 'n'; break;
        case CHAR_o: c = 'o'; break;
        case CHAR_p: c = 'p'; break;
        case CHAR_q: c = 'q'; break;
        case CHAR_r: c = 'r'; break;
        case CHAR_s: c = 's'; break;
        case CHAR_t: c = 't'; break;
        case CHAR_u: c = 'u'; break;
        case CHAR_v: c = 'v'; break;
        case CHAR_w: c = 'w'; break;
        case CHAR_x: c = 'x'; break;
        case CHAR_y: c = 'y'; break;
        case CHAR_z: c = 'z'; break;

        // Numbers
        case CHAR_0: c = '0'; break;
        case CHAR_1: c = '1'; break;
        case CHAR_2: c = '2'; break;
        case CHAR_3: c = '3'; break;
        case CHAR_4: c = '4'; break;
        case CHAR_5: c = '5'; break;
        case CHAR_6: c = '6'; break;
        case CHAR_7: c = '7'; break;
        case CHAR_8: c = '8'; break;
        case CHAR_9: c = '9'; break;

        // Whitespace and control
        case CHAR_SPACE:      c = ' ';  break;
        case CHAR_ENTER:      c = '\n'; break;
        case CHAR_TAB:        c = '\t'; break;
        case CHAR_BACKSPACE:  c = '\b'; break;

        // Symbols (main section, unshifted)
        case CHAR_MINUS:      c = '-';  break;
        case CHAR_EQUAL:      c = '=';  break;
        case CHAR_LBRACKET:   c = '[';  break;
        case CHAR_RBRACKET:   c = ']';  break;
        case CHAR_BACKSLASH:  c = '\\'; break;
        case CHAR_SEMICOLON:  c = ';';  break;
        case CHAR_APOSTROPHE: c = '\''; break;
        case CHAR_GRAVE:      c = '`';  break;
        case CHAR_COMMA:      c = ',';  break;
        case CHAR_DOT:        c = '.';  break;
        case CHAR_SLASH:      c = '/';  break;

        // Shifted symbols
        case CHAR_EXCLAMATION: c = '!'; break;
        case CHAR_AT:          c = '@'; break;
        case CHAR_HASH:        c = '#'; break;
        case CHAR_DOLLAR:      c = '$'; break;
        case CHAR_PERCENT:     c = '%'; break;
        case CHAR_CARET:       c = '^'; break;
        case CHAR_AMPERSAND:   c = '&'; break;
        case CHAR_ASTERISK:    c = '*'; break;
        case CHAR_LPAREN:      c = '('; break;
        case CHAR_RPAREN:      c = ')'; break;
        case CHAR_UNDERSCORE:  c = '_'; break;
        case CHAR_PLUS:        c = '+'; break;
        case CHAR_LCURLY:      c = '{'; break;
        case CHAR_RCURLY:      c = '}'; break;
        case CHAR_PIPE:        c = '|'; break;
        case CHAR_COLON:       c = ':'; break;
        case CHAR_QUOTE:       c = '"'; break;
        case CHAR_LESS:        c = '<'; break;
        case CHAR_GREATER:     c = '>'; break;
        case CHAR_QUESTION:    c = '?'; break;
        case CHAR_TILDE:       c = '~'; break;

        // AltGr/Right Alt symbols (common on international layouts)
        case CHAR_EURO:         c = '€'; break;
        case CHAR_SECTION:      c = '§'; break;
        case CHAR_DEGREE:       c = '°'; break;
        case CHAR_CEDILLA:      c = 'ç'; break;
        case CHAR_AE:           c = 'æ'; break;
        case CHAR_OE:           c = 'œ'; break;
        case CHAR_SHARP_S:      c = 'ß'; break;
        case CHAR_ACUTE:        c = '´'; break;
        case CHAR_GRAVE_ACCENT: c = '`'; break;
        case CHAR_CIRCUMFLEX:   c = '^'; break;
        case CHAR_TREMA:        c = '¨'; break;
        case CHAR_CURRENCY:     c = '¤'; break;

        // Non-drawable or special keys (do nothing)
        default: return RES_ERROR;
    }

    // Insert the character at the end of the buffer
    size_t len = strlen(buffer);
    buffer[len] = c;
    buffer[len + 1] = '\0';

    return RES_OK;
}


