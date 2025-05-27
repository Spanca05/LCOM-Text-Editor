#ifndef CHARACTER_H
#define CHARACTER_H

// Enum for every physical key with a scancode (standard 104/105-key PC keyboard)
// Includes shifted and AltGr symbols, formatted for clarity
typedef enum {
    CHAR_NONE = 0, // (none)

    // Lowercase Letters
    CHAR_a, // 'a'
    CHAR_b, // 'b'
    CHAR_c, // 'c'
    CHAR_d, // 'd'
    CHAR_e, // 'e'
    CHAR_f, // 'f'
    CHAR_g, // 'g'
    CHAR_h, // 'h'
    CHAR_i, // 'i'
    CHAR_j, // 'j'
    CHAR_k, // 'k'
    CHAR_l, // 'l'
    CHAR_m, // 'm'
    CHAR_n, // 'n'
    CHAR_o, // 'o'
    CHAR_p, // 'p'
    CHAR_q, // 'q'
    CHAR_r, // 'r'
    CHAR_s, // 's'
    CHAR_t, // 't'
    CHAR_u, // 'u'
    CHAR_v, // 'v'
    CHAR_w, // 'w'
    CHAR_x, // 'x'
    CHAR_y, // 'y'
    CHAR_z, // 'z'

    // Uppercase Letters
    CHAR_A, // 'A'
    CHAR_B, // 'B'
    CHAR_C, // 'C'
    CHAR_D, // 'D'
    CHAR_E, // 'E'
    CHAR_F, // 'F'
    CHAR_G, // 'G'
    CHAR_H, // 'H'
    CHAR_I, // 'I'
    CHAR_J, // 'J'
    CHAR_K, // 'K'
    CHAR_L, // 'L'
    CHAR_M, // 'M'
    CHAR_N, // 'N'
    CHAR_O, // 'O'
    CHAR_P, // 'P'
    CHAR_Q, // 'Q'
    CHAR_R, // 'R'
    CHAR_S, // 'S'
    CHAR_T, // 'T'
    CHAR_U, // 'U'
    CHAR_V, // 'V'
    CHAR_W, // 'W'
    CHAR_X, // 'X'
    CHAR_Y, // 'Y'
    CHAR_Z, // 'Z'

    // Numbers (top row)
    CHAR_1, // '1'
    CHAR_2, // '2'
    CHAR_3, // '3'
    CHAR_4, // '4'
    CHAR_5, // '5'
    CHAR_6, // '6'
    CHAR_7, // '7'
    CHAR_8, // '8'
    CHAR_9, // '9'
    CHAR_0, // '0'

    // Symbols (main section, unshifted)
    CHAR_ENTER,      // '\n'
    CHAR_ESC,        // (escape)
    CHAR_BACKSPACE,  // '\b'
    CHAR_TAB,        // '\t'
    CHAR_SPACE,      // ' '
    CHAR_MINUS,      // '-'
    CHAR_EQUAL,      // '='
    CHAR_LBRACKET,   // '['
    CHAR_RBRACKET,   // ']'
    CHAR_BACKSLASH,  // '\\'
    CHAR_SEMICOLON,  // ';'
    CHAR_APOSTROPHE, // '\''
    CHAR_GRAVE,      // '`'
    CHAR_COMMA,      // ','
    CHAR_DOT,        // '.'
    CHAR_SLASH,      // '/'

    // Shifted symbols (above numbers and main section)
    CHAR_EXCLAMATION, // '!'
    CHAR_AT,          // '@'
    CHAR_HASH,        // '#'
    CHAR_DOLLAR,      // '$'
    CHAR_PERCENT,     // '%'
    CHAR_CARET,       // '^'
    CHAR_AMPERSAND,   // '&'
    CHAR_ASTERISK,    // '*'
    CHAR_LPAREN,      // '('
    CHAR_RPAREN,      // ')'
    CHAR_UNDERSCORE,  // '_'
    CHAR_PLUS,        // '+'
    CHAR_LCURLY,      // '{'
    CHAR_RCURLY,      // '}'
    CHAR_PIPE,        // '|'
    CHAR_COLON,       // ':'
    CHAR_QUOTE,       // '"'
    CHAR_LESS,        // '<'
    CHAR_GREATER,     // '>'
    CHAR_QUESTION,    // '?'
    CHAR_TILDE,       // '~'

    // AltGr/Right Alt symbols (common on international layouts)
    CHAR_EURO,         // '€'
    CHAR_SECTION,      // '§'
    CHAR_DEGREE,       // '°'
    CHAR_CEDILLA,      // 'ç'
    CHAR_AE,           // 'æ'
    CHAR_OE,           // 'œ'
    CHAR_SHARP_S,      // 'ß'
    CHAR_ACUTE,        // '´'
    CHAR_GRAVE_ACCENT, // '`'
    CHAR_CIRCUMFLEX,   // '^'
    CHAR_TREMA,        // '¨'
    CHAR_CURRENCY,     // '¤'
    
    // Arrow keys
    CHAR_ARROW_UP,    // (Up Arrow)
    CHAR_ARROW_DOWN,  // (Down Arrow)
    CHAR_ARROW_LEFT,  // (Left Arrow)
    CHAR_ARROW_RIGHT, // (Right Arrow)
    
    // Modifier keys
    CHAR_LSHIFT,   // (Left Shift)
    CHAR_RSHIFT,   // (Right Shift)
    CHAR_LCTRL,    // (Left Ctrl)
    CHAR_RCTRL,    // (Right Ctrl)
    CHAR_LALT,     // (Left Alt)
    CHAR_RALT,     // (Right Alt)
    CHAR_CAPSLOCK, // (Caps Lock)
    // CHAR_LGUI, CHAR_RGUI, // (Windows/Command keys)
    

    //! For now, unnecessary keys
    // Function keys
    // (Uncomment if needed)
    // CHAR_F1, CHAR_F2, CHAR_F3, CHAR_F4, CHAR_F5, CHAR_F6,
    // CHAR_F7, CHAR_F8, CHAR_F9, CHAR_F10, CHAR_F11, CHAR_F12,


    // Navigation/edit keys
    // (Uncomment if needed)
    // CHAR_INSERT, CHAR_DELETE, CHAR_HOME, CHAR_END,
    // CHAR_PAGEUP, CHAR_PAGEDOWN,


    // Numpad keys
    // (Uncomment if needed)
    // CHAR_NUMLOCK, CHAR_NUMPAD_DIVIDE, CHAR_NUMPAD_ASTERISK, CHAR_NUMPAD_MINUS,
    // CHAR_NUMPAD_PLUS, CHAR_NUMPAD_ENTER, CHAR_NUMPAD_DOT,
    // CHAR_NUMPAD_0, CHAR_NUMPAD_1, CHAR_NUMPAD_2, CHAR_NUMPAD_3, CHAR_NUMPAD_4,
    // CHAR_NUMPAD_5, CHAR_NUMPAD_6, CHAR_NUMPAD_7, CHAR_NUMPAD_8, CHAR_NUMPAD_9,

    // Special keys
    // (Uncomment if needed)
    // CHAR_PRINT_SCREEN, CHAR_SCROLLLOCK, CHAR_PAUSE_BREAK, CHAR_MENU,

    // Extra (optional, not all keyboards)
    // CHAR_VOLUME_UP, CHAR_VOLUME_DOWN, CHAR_VOLUME_MUTE,
    // CHAR_MEDIA_NEXT, CHAR_MEDIA_PREV, CHAR_MEDIA_STOP, CHAR_MEDIA_PLAY
} Character;


#endif
