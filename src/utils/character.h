#ifndef CHARACTER_H
#define CHARACTER_H

// Enum for every physical key with a scancode (standard 104/105-key PC keyboard)
// Includes shifted and AltGr symbols, formatted for clarity
// Stil missing "acentos" fml
typedef enum {
    CHAR_NONE = 0, // (none)
    CHAR_ESC,      // (escape)

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
    CHAR_BACKSLASH,  // '\\'
    CHAR_APOSTROPHE, // '\''
    CHAR_LEFT_ANGLE, // '«'
    CHAR_BACKSPACE,  // '\b'
    CHAR_TAB,        // '\t'
    CHAR_PLUS,       // '+'
    CHAR_ACUTE,      // '´'
    CHAR_TILDE,      // '~'
    CHAR_CEDILLA,    // 'ç'
    CHAR_MOI,        // 'º' (Masculine Ordinal Indicator)
    CHAR_ENTER,      // '\n'
    CHAR_COMMA,      // ','
    CHAR_DOT,        // '.'
    CHAR_MINUS,      // '-'
    CHAR_SPACE,      // ' '
    CHAR_LESS,       // '<'

    // Shifted symbols (above numbers and main section)
    CHAR_PIPE,          // '|'
    CHAR_EXCLAMATION,   // '!'
    CHAR_QUOTE,         // '"'
    CHAR_HASH,          // '#'
    CHAR_DOLLAR,        // '$'
    CHAR_PERCENT,       // '%'
    CHAR_AMPERSAND,     // '&'
    CHAR_SLASH,         // '/'
    CHAR_LPAREN,        // '('
    CHAR_RPAREN,        // ')'
    CHAR_EQUAL,         // '='
    CHAR_QUESTION,      // '?'
    CHAR_RIGHT_ANGLE,   // '»'
    CHAR_ASTERISK,      // '*'
    CHAR_GRAVE,         // '`'
    CHAR_CIRCUMFLEX,    // '^'
    CHAR_CEDILLA_UPPER, // 'Ç'
    CHAR_FOI,           // 'ª' (Feminine Ordinal Indicator)
    CHAR_SEMICOLON,     // ';'
    CHAR_COLON,         // ':'
    CHAR_UNDERSCORE,    // '_'
    CHAR_GREATER,       // '>'


    // AltGr/Right Alt symbols (common on international layouts)
    CHAR_AT,       // '@'
    CHAR_POUND,    // '£'
    CHAR_SECTION,  // '§'
    CHAR_EURO,     // '€'
    CHAR_LCURLY,   // '{'
    CHAR_LBRACKET, // '['
    CHAR_RBRACKET, // ']'
    CHAR_RCURLY,   // '}'
    CHAR_TREMA,    // '¨'

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

static const char *character_to_char_map[] = {
    [CHAR_NONE] = NULL, // (none)
    [CHAR_ESC]  = NULL, // (escape)

    // Lowercase Letters
    [CHAR_a] = "a",
    [CHAR_b] = "b",
    [CHAR_c] = "c",
    [CHAR_d] = "d",
    [CHAR_e] = "e",
    [CHAR_f] = "f",
    [CHAR_g] = "g",
    [CHAR_h] = "h",
    [CHAR_i] = "i",
    [CHAR_j] = "j",
    [CHAR_k] = "k",
    [CHAR_l] = "l",
    [CHAR_m] = "m",
    [CHAR_n] = "n",
    [CHAR_o] = "o",
    [CHAR_p] = "p",
    [CHAR_q] = "q",
    [CHAR_r] = "r",
    [CHAR_s] = "s",
    [CHAR_t] = "t",
    [CHAR_u] = "u",
    [CHAR_v] = "v",
    [CHAR_w] = "w",
    [CHAR_x] = "x",
    [CHAR_y] = "y",
    [CHAR_z] = "z",

    // Uppercase Letters
    [CHAR_A] = "A",
    [CHAR_B] = "B",
    [CHAR_C] = "C",
    [CHAR_D] = "D",
    [CHAR_E] = "E",
    [CHAR_F] = "F",
    [CHAR_G] = "G",
    [CHAR_H] = "H",
    [CHAR_I] = "I",
    [CHAR_J] = "J",
    [CHAR_K] = "K",
    [CHAR_L] = "L",
    [CHAR_M] = "M",
    [CHAR_N] = "N",
    [CHAR_O] = "O",
    [CHAR_P] = "P",
    [CHAR_Q] = "Q",
    [CHAR_R] = "R",
    [CHAR_S] = "S",
    [CHAR_T] = "T",
    [CHAR_U] = "U",
    [CHAR_V] = "V",
    [CHAR_W] = "W",
    [CHAR_X] = "X",
    [CHAR_Y] = "Y",
    [CHAR_Z] = "Z",

    // Numbers (top row)
    [CHAR_1] = "1",
    [CHAR_2] = "2",
    [CHAR_3] = "3",
    [CHAR_4] = "4",
    [CHAR_5] = "5",
    [CHAR_6] = "6",
    [CHAR_7] = "7",
    [CHAR_8] = "8",
    [CHAR_9] = "9",
    [CHAR_0] = "0",

    // Symbols (main section, unshifted)
    [CHAR_BACKSLASH]  = "\\",       // '\\'
    [CHAR_APOSTROPHE] = "'",        // '\''
    [CHAR_LEFT_ANGLE] = "\xC2\xAB", // '«' (UTF-8)
    [CHAR_BACKSPACE]  = "\b",       // '\b'
    [CHAR_TAB]        = "\t",       // '\t'
    [CHAR_PLUS]       = "+",        // '+'
    [CHAR_ACUTE]      = "\xC2\xB4", // '´' (UTF-8)
    [CHAR_TILDE]      = "~",        // '~'
    [CHAR_CEDILLA]    = "\xC3\xA7", // 'ç' (UTF-8)
    [CHAR_MOI]        = "\xC2\xBA", // 'º' (UTF-8)
    [CHAR_ENTER]      = "\n",       // '\n'
    [CHAR_COMMA]      = ",",        // ','
    [CHAR_DOT]        = ".",        // '.'
    [CHAR_MINUS]      = "-",        // '-'
    [CHAR_SPACE]      = " ",        // ' '
    [CHAR_LESS]       = "<",        // '<'

    // Shifted symbols (above numbers and main section)
    [CHAR_EXCLAMATION]   = "!",        // '!'
    [CHAR_HASH]          = "#",        // '#'
    [CHAR_DOLLAR]        = "$",        // '$'
    [CHAR_PERCENT]       = "%",        // '%'
    [CHAR_CIRCUMFLEX]    = "^",        // '^'
    [CHAR_AMPERSAND]     = "&",        // '&'
    [CHAR_ASTERISK]      = "*",        // '*'
    [CHAR_GRAVE]         = "`",        // '`'
    [CHAR_SLASH]         = "/",        // '/'
    [CHAR_LPAREN]        = "(",        // '('
    [CHAR_RPAREN]        = ")",        // ')'
    [CHAR_EQUAL]         = "=",        // '='
    [CHAR_UNDERSCORE]    = "_",        // '_'
    [CHAR_PIPE]          = "|",        // '|'
    [CHAR_SEMICOLON]     = ";",        // ';'
    [CHAR_COLON]         = ":",        // ':'
    [CHAR_QUOTE]         = "\"",       // '"'
    [CHAR_GREATER]       = ">",        // '>'
    [CHAR_QUESTION]      = "?",        // '?'
    [CHAR_RIGHT_ANGLE]   = "\xC2\xBB", // '»'
    [CHAR_FOI]           = "\xC2\xAA", // 'ª'
    [CHAR_CEDILLA_UPPER] = "\xC3\x87", // 'Ç'


    // AltGr/Right Alt symbols (common on international layouts)
    [CHAR_AT]       = "@",            // '@'
    [CHAR_POUND]    = "\xC2\xA3",     // '£' (UTF-8)
    [CHAR_SECTION]  = "\xC2\xA7",     // '§' (UTF-8)
    [CHAR_EURO]     = "\xE2\x82\xAC", // '€' (UTF-8)
    [CHAR_LCURLY]   = "{",            // '{'
    [CHAR_LBRACKET] = "[",            // '['
    [CHAR_RBRACKET] = "]",            // ']'
    [CHAR_RCURLY]   = "}",            // '}'
    [CHAR_TREMA]    = "\xC2\xA8",     // '¨' (UTF-8)

    // Arrow keys (no printable char)
    [CHAR_ARROW_UP]    = NULL,
    [CHAR_ARROW_DOWN]  = NULL,
    [CHAR_ARROW_LEFT]  = NULL,
    [CHAR_ARROW_RIGHT] = NULL,

    // Modifier keys (no printable char)
    [CHAR_LSHIFT]   = NULL,
    [CHAR_RSHIFT]   = NULL,
    [CHAR_LCTRL]    = NULL,
    [CHAR_RCTRL]    = NULL,
    [CHAR_LALT]     = NULL,
    [CHAR_RALT]     = NULL,
    [CHAR_CAPSLOCK] = NULL,
};

// Maps each Character to its shifted version
static const Character shift_character_map[] = {
    // Lowercase Letters
    [CHAR_a] = CHAR_A,
    [CHAR_b] = CHAR_B,
    [CHAR_c] = CHAR_C,
    [CHAR_d] = CHAR_D,
    [CHAR_e] = CHAR_E,
    [CHAR_f] = CHAR_F,
    [CHAR_g] = CHAR_G,
    [CHAR_h] = CHAR_H,
    [CHAR_i] = CHAR_I,
    [CHAR_j] = CHAR_J,
    [CHAR_k] = CHAR_K,
    [CHAR_l] = CHAR_L,
    [CHAR_m] = CHAR_M,
    [CHAR_n] = CHAR_N,
    [CHAR_o] = CHAR_O,
    [CHAR_p] = CHAR_P,
    [CHAR_q] = CHAR_Q,
    [CHAR_r] = CHAR_R,
    [CHAR_s] = CHAR_S,
    [CHAR_t] = CHAR_T,
    [CHAR_u] = CHAR_U,
    [CHAR_v] = CHAR_V,
    [CHAR_w] = CHAR_W,
    [CHAR_x] = CHAR_X,
    [CHAR_y] = CHAR_Y,
    [CHAR_z] = CHAR_Z,

    // Numbers (top row)
    [CHAR_1] = CHAR_EXCLAMATION, // '!
    [CHAR_2] = CHAR_QUOTE,       // '"'
    [CHAR_3] = CHAR_HASH,        // '#'
    [CHAR_4] = CHAR_DOLLAR,      // '$'
    [CHAR_5] = CHAR_PERCENT,     // '%'
    [CHAR_6] = CHAR_AMPERSAND,   // '&'
    [CHAR_7] = CHAR_SLASH,       // '/'
    [CHAR_8] = CHAR_LPAREN,      // '('
    [CHAR_9] = CHAR_RPAREN,      // ')'
    [CHAR_0] = CHAR_EQUAL,       // '='

    // Symbols (main section, unshifted)
    [CHAR_BACKSLASH]  = CHAR_PIPE,          // '\' -> '|'
    [CHAR_APOSTROPHE] = CHAR_QUESTION,      // '\'' -> '?'
    [CHAR_LEFT_ANGLE] = CHAR_RIGHT_ANGLE,   // '«' -> '»'
    [CHAR_PLUS]       = CHAR_ASTERISK,      // '+' -> '*'
    [CHAR_ACUTE]      = CHAR_GRAVE,         // '´' -> '`'
    [CHAR_TILDE]      = CHAR_CIRCUMFLEX,    // '~' -> '^'
    [CHAR_CEDILLA]    = CHAR_CEDILLA_UPPER, //'ç' -> 'Ç'
    [CHAR_MOI]        = CHAR_FOI,           //'º' -> 'ª'
    [CHAR_COMMA]      = CHAR_SEMICOLON,     // ',' -> ';'
    [CHAR_DOT]        = CHAR_COLON,         // '.' -> ':'
    [CHAR_MINUS]      = CHAR_UNDERSCORE,    // '-' -> '_'
    [CHAR_LESS]       = CHAR_GREATER,       // '<' -> '>'
};

static const Character ralt_character_map[] = {
    // Numbers (top row)
    [CHAR_2] = CHAR_AT,       // '@'
    [CHAR_3] = CHAR_POUND,    // '£'
    [CHAR_4] = CHAR_SECTION,  // '§'
    [CHAR_5] = CHAR_EURO,     // '€'
    [CHAR_7] = CHAR_LCURLY,   // '{'
    [CHAR_8] = CHAR_LBRACKET, // '['
    [CHAR_9] = CHAR_RBRACKET, // ']'
    [CHAR_0] = CHAR_RCURLY,   // '}'

    // Symbols (main section, unshifted)
    [CHAR_PLUS]  = CHAR_TREMA,    // '+' -> '¨'
    [CHAR_ACUTE] = CHAR_RBRACKET, // '´' -> ']'
};


#endif
