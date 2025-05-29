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

    //

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
    CHAR_TAB,        // '\t'
    CHAR_PLUS,       // '+'
    CHAR_ACUTE,      // '`'
    CHAR_TILDE,      // '~'
    CHAR_CEDILLA,    // 'ç'
    CHAR_MOI,        // 'º' (Masculine Ordinal Indicator)
    CHAR_NEWLINE,    // '\n'
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
    CHAR_GRAVE,         // '´'
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


    // Letters with accent marks (lowercase)
    CHAR_a_ACUTE,  // 'à'
    CHAR_a_GRAVE,  // 'á'
    CHAR_a_CIRC,   // 'â'
    CHAR_a_TILDE,  // 'ã'
    CHAR_a_UMLAUT, // 'ä'
    CHAR_a_RING,   // 'å'
    CHAR_e_ACUTE,  // 'é'
    CHAR_e_GRAVE,  // 'è'
    CHAR_e_CIRC,   // 'ê'
    CHAR_e_UMLAUT, // 'ë'
    CHAR_i_ACUTE,  // 'í'
    CHAR_i_GRAVE,  // 'ì'
    CHAR_i_CIRC,   // 'î'
    CHAR_i_UMLAUT, // 'ï'
    CHAR_o_ACUTE,  // 'ó'
    CHAR_o_GRAVE,  // 'ò'
    CHAR_o_CIRC,   // 'ô'
    CHAR_o_TILDE,  // 'õ'
    CHAR_o_UMLAUT, // 'ö'
    CHAR_u_ACUTE,  // 'ú'
    CHAR_u_GRAVE,  // 'ù'
    CHAR_u_CIRC,   // 'û'
    CHAR_u_UMLAUT, // 'ü'

    // Letters with accent marks (uppercase)
    CHAR_A_ACUTE_UPPER,  // 'Á'
    CHAR_A_GRAVE_UPPER,  // 'À'
    CHAR_A_CIRC_UPPER,   // 'Â'
    CHAR_A_TILDE_UPPER,  // 'Ã'
    CHAR_A_UMLAUT_UPPER, // 'Ä'
    CHAR_A_RING_UPPER,   // 'Å'
    CHAR_E_ACUTE_UPPER,  // 'É'
    CHAR_E_GRAVE_UPPER,  // 'È'
    CHAR_E_CIRC_UPPER,   // 'Ê'
    CHAR_E_UMLAUT_UPPER, // 'Ë'
    CHAR_I_ACUTE_UPPER,  // 'Í'
    CHAR_I_GRAVE_UPPER,  // 'Ì'
    CHAR_I_CIRC_UPPER,   // 'Î'
    CHAR_I_UMLAUT_UPPER, // 'Ï'
    CHAR_O_ACUTE_UPPER,  // 'Ó'
    CHAR_O_GRAVE_UPPER,  // 'Ò'
    CHAR_O_CIRC_UPPER,   // 'Ô'
    CHAR_O_TILDE_UPPER,  // 'Õ'
    CHAR_O_UMLAUT_UPPER, // 'Ö'
    CHAR_U_ACUTE_UPPER,  // 'Ú'
    CHAR_U_GRAVE_UPPER,  // 'Ù'
    CHAR_U_CIRC_UPPER,   // 'Û'
    CHAR_U_UMLAUT_UPPER, // 'Ü'
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
    [CHAR_TAB]        = "\t",       // '\t'
    [CHAR_PLUS]       = "+",        // '+'
    [CHAR_ACUTE]      = "\xC2\xB4", // '´' (UTF-8)
    [CHAR_TILDE]      = "~",        // '~'
    [CHAR_CEDILLA]    = "\xC3\xA7", // 'ç' (UTF-8)
    [CHAR_MOI]        = "\xC2\xBA", // 'º' (UTF-8)
    [CHAR_NEWLINE]    = "\n",       // '\n'
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
