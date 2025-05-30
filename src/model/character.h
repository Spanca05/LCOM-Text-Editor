#ifndef CHARACTER_H
#define CHARACTER_H

#include "../utils/result.h"
#include "key.h"
#include "modifiers.h"

// Enum for every Character in the English and Portuguese alphabet
typedef enum Character {
    CHAR_NONE = 0,      // (none)

    CHAR_a,             // 'a'
    CHAR_b,             // 'b'
    CHAR_c,             // 'c'
    CHAR_d,             // 'd'
    CHAR_e,             // 'e'
    CHAR_f,             // 'f'
    CHAR_g,             // 'g'
    CHAR_h,             // 'h'
    CHAR_i,             // 'i'
    CHAR_j,             // 'j'
    CHAR_k,             // 'k'
    CHAR_l,             // 'l'
    CHAR_m,             // 'm'
    CHAR_n,             // 'n'
    CHAR_o,             // 'o'
    CHAR_p,             // 'p'
    CHAR_q,             // 'q'
    CHAR_r,             // 'r'
    CHAR_s,             // 's'
    CHAR_t,             // 't'
    CHAR_u,             // 'u'
    CHAR_v,             // 'v'
    CHAR_w,             // 'w'
    CHAR_x,             // 'x'
    CHAR_y,             // 'y'
    CHAR_z,             // 'z'


    CHAR_A,             // 'A'
    CHAR_B,             // 'B'
    CHAR_C,             // 'C'
    CHAR_D,             // 'D'
    CHAR_E,             // 'E'
    CHAR_F,             // 'F'
    CHAR_G,             // 'G'
    CHAR_H,             // 'H'
    CHAR_I,             // 'I'
    CHAR_J,             // 'J'
    CHAR_K,             // 'K'
    CHAR_L,             // 'L'
    CHAR_M,             // 'M'
    CHAR_N,             // 'N'
    CHAR_O,             // 'O'
    CHAR_P,             // 'P'
    CHAR_Q,             // 'Q'
    CHAR_R,             // 'R'
    CHAR_S,             // 'S'
    CHAR_T,             // 'T'
    CHAR_U,             // 'U'
    CHAR_V,             // 'V'
    CHAR_W,             // 'W'
    CHAR_X,             // 'X'
    CHAR_Y,             // 'Y'
    CHAR_Z,             // 'Z'


    CHAR_1,             // '1'
    CHAR_2,             // '2'
    CHAR_3,             // '3'
    CHAR_4,             // '4'
    CHAR_5,             // '5'
    CHAR_6,             // '6'
    CHAR_7,             // '7'
    CHAR_8,             // '8'
    CHAR_9,             // '9'
    CHAR_0,             // '0'


    CHAR_BACKSLASH,     // '\'
    CHAR_APOSTROPHE,    // '''
    CHAR_LEFT_ANGLE,    // '«'
    CHAR_TAB,           // '\t'
    CHAR_PLUS,          // '+'
    CHAR_ACUTE,         // '´'
    CHAR_TILDE,         // '~'
    CHAR_CEDILLA,       // 'ç'
    CHAR_MOI,           // 'º' (Masculine Ordinal Indicator)
    CHAR_NEWLINE,       // '\n'
    CHAR_COMMA,         // ','
    CHAR_DOT,           // '.'
    CHAR_MINUS,         // '-'
    CHAR_SPACE,         // ' '
    CHAR_LESS,          // '<'


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


    CHAR_AT,            // '@'
    CHAR_POUND,         // '£'
    CHAR_SECTION,       // '§'
    CHAR_EURO,          // '€'
    CHAR_LCURLY,        // '{'
    CHAR_LBRACKET,      // '['
    CHAR_RBRACKET,      // ']'
    CHAR_RCURLY,        // '}'
    CHAR_TREMA,         // '¨'


    CHAR_a_ACUTE,       // 'á'
    CHAR_a_GRAVE,       // 'à'
    CHAR_a_CIRC,        // 'â'
    CHAR_a_TILDE,       // 'ã'
    CHAR_a_UMLAUT,      // 'ä'
    CHAR_a_RING,        // 'å'
    CHAR_e_ACUTE,       // 'é'
    CHAR_e_GRAVE,       // 'è'
    CHAR_e_CIRC,        // 'ê'
    CHAR_e_UMLAUT,      // 'ë'
    CHAR_i_ACUTE,       // 'í'
    CHAR_i_GRAVE,       // 'ì'
    CHAR_i_CIRC,        // 'î'
    CHAR_i_UMLAUT,      // 'ï'
    CHAR_o_ACUTE,       // 'ó'
    CHAR_o_GRAVE,       // 'ò'
    CHAR_o_CIRC,        // 'ô'
    CHAR_o_TILDE,       // 'õ'
    CHAR_o_UMLAUT,      // 'ö'
    CHAR_u_ACUTE,       // 'ú'
    CHAR_u_GRAVE,       // 'ù'
    CHAR_u_CIRC,        // 'û'
    CHAR_u_UMLAUT,      // 'ü'


    CHAR_A_ACUTE,       // 'Á'
    CHAR_A_GRAVE,       // 'À'
    CHAR_A_CIRC,        // 'Â'
    CHAR_A_TILDE,       // 'Ã'
    CHAR_A_UMLAUT,      // 'Ä'
    CHAR_A_RING,        // 'Å'
    CHAR_E_ACUTE,       // 'É'
    CHAR_E_GRAVE,       // 'È'
    CHAR_E_CIRC,        // 'Ê'
    CHAR_E_UMLAUT,      // 'Ë'
    CHAR_I_ACUTE,       // 'Í'
    CHAR_I_GRAVE,       // 'Ì'
    CHAR_I_CIRC,        // 'Î'
    CHAR_I_UMLAUT,      // 'Ï'
    CHAR_O_ACUTE,       // 'Ó'
    CHAR_O_GRAVE,       // 'Ò'
    CHAR_O_CIRC,        // 'Ô'
    CHAR_O_TILDE,       // 'Õ'
    CHAR_O_UMLAUT,      // 'Ö'
    CHAR_U_ACUTE,       // 'Ú'
    CHAR_U_GRAVE,       // 'Ù'
    CHAR_U_CIRC,        // 'Û'
    CHAR_U_UMLAUT,      // 'Ü'
} Character;

Result key_to_character(Key key, Modifiers modifiers, Character *character, bool *textModifierUsed);

bool character_is_text_modifier(Character character);

TextModifier character_to_text_modifier(Character character);

Character text_modifier_to_character(TextModifier textModifier);

const char* character_to_utf8(Character character);

extern const char *character_names[];

#endif // CHARACTER_H
