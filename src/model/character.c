#include <stdlib.h>

#include "../utils/result.h"
#include "character.h"
#include "key.h"
#include "modifiers.h"

Result key_to_character(Key key, Modifiers modifiers, Character *character, bool *textModifierUsed) {
    if (!character) return RES_INVALID_ARGUMENT;
    if (!textModifierUsed) return RES_INVALID_ARGUMENT;

    // Modifiers that block text
    if (modifiers.ctrl) return RES_DOES_NOT_EXIST;
    if (modifiers.lalt) return RES_DOES_NOT_EXIST;

    *textModifierUsed = false;
    bool capitalize   = modifiers.shift ^ modifiers.caps_lock;

    switch (key) {
    case KEY_a:
        *textModifierUsed = true;
        switch (modifiers.textModifier) {
        case TEXT_MOD_ACUTE_ACCENT     : *character = capitalize ? CHAR_A_ACUTE : CHAR_a_ACUTE; break;
        case TEXT_MOD_GRAVE_ACCENT     : *character = capitalize ? CHAR_A_GRAVE : CHAR_a_GRAVE; break;
        case TEXT_MOD_CIRCUMFLEX_ACCENT: *character = capitalize ? CHAR_A_CIRC : CHAR_a_CIRC; break;
        case TEXT_MOD_TILL_ACCENT      : *character = capitalize ? CHAR_A_TILDE : CHAR_a_TILDE; break;
        case TEXT_MOD_UMLAUT           : *character = capitalize ? CHAR_A_UMLAUT : CHAR_a_UMLAUT; break;
        default:
            *character        = capitalize ? CHAR_A : CHAR_a;
            *textModifierUsed = false;
            break;
        }
        break;
    case KEY_e:
        *textModifierUsed = true;
        switch (modifiers.textModifier) {
        case TEXT_MOD_ACUTE_ACCENT     : *character = capitalize ? CHAR_E_ACUTE : CHAR_e_ACUTE; break;
        case TEXT_MOD_GRAVE_ACCENT     : *character = capitalize ? CHAR_E_GRAVE : CHAR_e_GRAVE; break;
        case TEXT_MOD_CIRCUMFLEX_ACCENT: *character = capitalize ? CHAR_E_CIRC : CHAR_e_CIRC; break;
        case TEXT_MOD_UMLAUT           : *character = capitalize ? CHAR_E_UMLAUT : CHAR_e_UMLAUT; break;
        default:
            *character        = capitalize ? CHAR_E : CHAR_e;
            *textModifierUsed = false;
            break;
        }
        break;
    case KEY_i:
        *textModifierUsed = true;
        switch (modifiers.textModifier) {
        case TEXT_MOD_ACUTE_ACCENT     : *character = capitalize ? CHAR_I_ACUTE : CHAR_i_ACUTE; break;
        case TEXT_MOD_GRAVE_ACCENT     : *character = capitalize ? CHAR_I_GRAVE : CHAR_i_GRAVE; break;
        case TEXT_MOD_CIRCUMFLEX_ACCENT: *character = capitalize ? CHAR_I_CIRC : CHAR_i_CIRC; break;
        case TEXT_MOD_UMLAUT           : *character = capitalize ? CHAR_I_UMLAUT : CHAR_i_UMLAUT; break;
        default:
            *character        = capitalize ? CHAR_I : CHAR_i;
            *textModifierUsed = false;
            break;
        }
        break;
    case KEY_o:
        *textModifierUsed = true;
        switch (modifiers.textModifier) {
        case TEXT_MOD_ACUTE_ACCENT     : *character = capitalize ? CHAR_O_ACUTE : CHAR_o_ACUTE; break;
        case TEXT_MOD_GRAVE_ACCENT     : *character = capitalize ? CHAR_O_GRAVE : CHAR_o_GRAVE; break;
        case TEXT_MOD_CIRCUMFLEX_ACCENT: *character = capitalize ? CHAR_O_CIRC : CHAR_o_CIRC; break;
        case TEXT_MOD_TILL_ACCENT      : *character = capitalize ? CHAR_O_TILDE : CHAR_o_TILDE; break;
        case TEXT_MOD_UMLAUT           : *character = capitalize ? CHAR_O_UMLAUT : CHAR_o_UMLAUT; break;
        default:
            *character        = capitalize ? CHAR_O : CHAR_o;
            *textModifierUsed = false;
            break;
        }
        break;
    case KEY_u:
        *textModifierUsed = true;
        switch (modifiers.textModifier) {
        case TEXT_MOD_ACUTE_ACCENT     : *character = capitalize ? CHAR_U_ACUTE : CHAR_u_ACUTE; break;
        case TEXT_MOD_GRAVE_ACCENT     : *character = capitalize ? CHAR_U_GRAVE : CHAR_u_GRAVE; break;
        case TEXT_MOD_CIRCUMFLEX_ACCENT: *character = capitalize ? CHAR_U_CIRC : CHAR_u_CIRC; break;
        case TEXT_MOD_UMLAUT           : *character = capitalize ? CHAR_U_UMLAUT : CHAR_u_UMLAUT; break;
        default:
            *character        = capitalize ? CHAR_U : CHAR_u;
            *textModifierUsed = false;
            break;
        }
        break;

    case KEY_b      : *character = capitalize ? CHAR_B : CHAR_b; break;
    case KEY_c      : *character = capitalize ? CHAR_C : CHAR_c; break;
    case KEY_d      : *character = capitalize ? CHAR_D : CHAR_d; break;
    case KEY_f      : *character = capitalize ? CHAR_F : CHAR_f; break;
    case KEY_g      : *character = capitalize ? CHAR_G : CHAR_g; break;
    case KEY_h      : *character = capitalize ? CHAR_H : CHAR_h; break;
    case KEY_j      : *character = capitalize ? CHAR_J : CHAR_j; break;
    case KEY_k      : *character = capitalize ? CHAR_K : CHAR_k; break;
    case KEY_l      : *character = capitalize ? CHAR_L : CHAR_l; break;
    case KEY_m      : *character = capitalize ? CHAR_M : CHAR_m; break;
    case KEY_n      : *character = capitalize ? CHAR_N : CHAR_n; break;
    case KEY_p      : *character = capitalize ? CHAR_P : CHAR_p; break;
    case KEY_q      : *character = capitalize ? CHAR_Q : CHAR_q; break;
    case KEY_r      : *character = capitalize ? CHAR_R : CHAR_r; break;
    case KEY_s      : *character = capitalize ? CHAR_S : CHAR_s; break;
    case KEY_t      : *character = capitalize ? CHAR_T : CHAR_t; break;
    case KEY_v      : *character = capitalize ? CHAR_V : CHAR_v; break;
    case KEY_w      : *character = capitalize ? CHAR_W : CHAR_w; break;
    case KEY_x      : *character = capitalize ? CHAR_X : CHAR_x; break;
    case KEY_y      : *character = capitalize ? CHAR_Y : CHAR_y; break;
    case KEY_z      : *character = capitalize ? CHAR_Z : CHAR_z; break;
    case KEY_CEDILLA: *character = capitalize ? CHAR_CEDILLA_UPPER : CHAR_CEDILLA; break;


    case KEY_1: *character = modifiers.shift ? CHAR_EXCLAMATION : CHAR_1; break;
    case KEY_2: *character = modifiers.ralt ? CHAR_AT : (modifiers.shift ? CHAR_QUOTE : CHAR_2); break;
    case KEY_3: *character = modifiers.ralt ? CHAR_POUND : (modifiers.shift ? CHAR_HASH : CHAR_3); break;
    case KEY_4: *character = modifiers.ralt ? CHAR_SECTION : (modifiers.shift ? CHAR_DOLLAR : CHAR_4); break;
    case KEY_5: *character = modifiers.ralt ? CHAR_EURO : (modifiers.shift ? CHAR_PERCENT : CHAR_5); break;
    case KEY_6: *character = modifiers.shift ? CHAR_AMPERSAND : CHAR_6; break;
    case KEY_7: *character = modifiers.ralt ? CHAR_LCURLY : (modifiers.shift ? CHAR_SLASH : CHAR_7); break;
    case KEY_8: *character = modifiers.ralt ? CHAR_LBRACKET : (modifiers.shift ? CHAR_LPAREN : CHAR_8); break;
    case KEY_9: *character = modifiers.ralt ? CHAR_RBRACKET : (modifiers.shift ? CHAR_RPAREN : CHAR_9); break;
    case KEY_0: *character = modifiers.ralt ? CHAR_RCURLY : (modifiers.shift ? CHAR_EQUAL : CHAR_0); break;


    case KEY_BACKSLASH : *character = modifiers.shift ? CHAR_PIPE : CHAR_BACKSLASH; break;
    case KEY_TAB       : *character = CHAR_TAB; break;
    case KEY_SPACE     : *character = CHAR_SPACE; break;
    case KEY_APOSTROPHE: *character = modifiers.shift ? CHAR_QUESTION : CHAR_APOSTROPHE; break;
    case KEY_QUOTE     : *character = modifiers.shift ? CHAR_RIGHT_ANGLE : CHAR_LEFT_ANGLE; break;
    case KEY_ORDINAL   : *character = modifiers.shift ? CHAR_FOI : CHAR_MOI; break;
    case KEY_ANGLE     : *character = modifiers.shift ? CHAR_GREATER : CHAR_LESS; break;
    case KEY_COMMA     : *character = modifiers.shift ? CHAR_SEMICOLON : CHAR_COMMA; break;
    case KEY_DOT       : *character = modifiers.shift ? CHAR_COLON : CHAR_DOT; break;
    case KEY_MINUS     : *character = modifiers.shift ? CHAR_UNDERSCORE : CHAR_MINUS; break;


    case KEY_PLUS  : *character = modifiers.ralt ? CHAR_TREMA : (modifiers.shift ? CHAR_ASTERISK : CHAR_PLUS); break;
    case KEY_ACCENT: *character = modifiers.shift ? CHAR_GRAVE : CHAR_ACUTE; break;
    case KEY_TILL  : *character = modifiers.shift ? CHAR_CIRCUMFLEX : CHAR_TILDE; break;


    default: return RES_DOES_NOT_EXIST;
    }

    return RES_OK;
}

bool character_is_text_modifier(Character character) {
    switch (character) {
    case CHAR_ACUTE:
    case CHAR_GRAVE:
    case CHAR_TILDE:
    case CHAR_CIRCUMFLEX:
    case CHAR_TREMA     : return true;
    default             : return false;
    }
}

TextModifier character_to_text_modifier(Character character) {
    switch (character) {
    case CHAR_ACUTE     : return TEXT_MOD_ACUTE_ACCENT;
    case CHAR_GRAVE     : return TEXT_MOD_GRAVE_ACCENT;
    case CHAR_TILDE     : return TEXT_MOD_TILL_ACCENT;
    case CHAR_CIRCUMFLEX: return TEXT_MOD_CIRCUMFLEX_ACCENT;
    case CHAR_TREMA     : return TEXT_MOD_UMLAUT;
    default             : return TEXT_MOD_NONE;
    }
}

Character text_modifier_to_character(TextModifier textModifier) {
    switch (textModifier) {
    case TEXT_MOD_ACUTE_ACCENT     : return CHAR_ACUTE;
    case TEXT_MOD_GRAVE_ACCENT     : return CHAR_GRAVE;
    case TEXT_MOD_TILL_ACCENT      : return CHAR_TILDE;
    case TEXT_MOD_CIRCUMFLEX_ACCENT: return CHAR_CIRCUMFLEX;
    case TEXT_MOD_UMLAUT           : return CHAR_TREMA;
    default                        : return CHAR_NONE;
    }
}

Result string_to_characters(char *string, uint64_t n, Character **characters) {
    if (!string || !characters) return RES_INVALID_ARGUMENT;

    *characters = (Character *)malloc(n * sizeof(Character));
    if (!*characters) return RES_MEMORY_ERROR;

    for (uint64_t i = 0; i < n; i++) {
        switch (string[i]) {
        case 'a' : (*characters)[i] = CHAR_a; break;
        case 'b' : (*characters)[i] = CHAR_b; break;
        case 'c' : (*characters)[i] = CHAR_c; break;
        case 'd' : (*characters)[i] = CHAR_d; break;
        case 'e' : (*characters)[i] = CHAR_e; break;
        case 'f' : (*characters)[i] = CHAR_f; break;
        case 'g' : (*characters)[i] = CHAR_g; break;
        case 'h' : (*characters)[i] = CHAR_h; break;
        case 'i' : (*characters)[i] = CHAR_i; break;
        case 'j' : (*characters)[i] = CHAR_j; break;
        case 'k' : (*characters)[i] = CHAR_k; break;
        case 'l' : (*characters)[i] = CHAR_l; break;
        case 'm' : (*characters)[i] = CHAR_m; break;
        case 'n' : (*characters)[i] = CHAR_n; break;
        case 'o' : (*characters)[i] = CHAR_o; break;
        case 'p' : (*characters)[i] = CHAR_p; break;
        case 'q' : (*characters)[i] = CHAR_q; break;
        case 'r' : (*characters)[i] = CHAR_r; break;
        case 's' : (*characters)[i] = CHAR_s; break;
        case 't' : (*characters)[i] = CHAR_t; break;
        case 'u' : (*characters)[i] = CHAR_u; break;
        case 'v' : (*characters)[i] = CHAR_v; break;
        case 'w' : (*characters)[i] = CHAR_w; break;
        case 'x' : (*characters)[i] = CHAR_x; break;
        case 'y' : (*characters)[i] = CHAR_y; break;
        case 'z' : (*characters)[i] = CHAR_z; break;
        case 'A' : (*characters)[i] = CHAR_A; break;
        case 'B' : (*characters)[i] = CHAR_B; break;
        case 'C' : (*characters)[i] = CHAR_C; break;
        case 'D' : (*characters)[i] = CHAR_D; break;
        case 'E' : (*characters)[i] = CHAR_E; break;
        case 'F' : (*characters)[i] = CHAR_F; break;
        case 'G' : (*characters)[i] = CHAR_G; break;
        case 'H' : (*characters)[i] = CHAR_H; break;
        case 'I' : (*characters)[i] = CHAR_I; break;
        case 'J' : (*characters)[i] = CHAR_J; break;
        case 'K' : (*characters)[i] = CHAR_K; break;
        case 'L' : (*characters)[i] = CHAR_L; break;
        case 'M' : (*characters)[i] = CHAR_M; break;
        case 'N' : (*characters)[i] = CHAR_N; break;
        case 'O' : (*characters)[i] = CHAR_O; break;
        case 'P' : (*characters)[i] = CHAR_P; break;
        case 'Q' : (*characters)[i] = CHAR_Q; break;
        case 'R' : (*characters)[i] = CHAR_R; break;
        case 'S' : (*characters)[i] = CHAR_S; break;
        case 'T' : (*characters)[i] = CHAR_T; break;
        case 'U' : (*characters)[i] = CHAR_U; break;
        case 'V' : (*characters)[i] = CHAR_V; break;
        case 'W' : (*characters)[i] = CHAR_W; break;
        case 'X' : (*characters)[i] = CHAR_X; break;
        case 'Y' : (*characters)[i] = CHAR_Y; break;
        case 'Z' : (*characters)[i] = CHAR_Z; break;
        case '1' : (*characters)[i] = CHAR_1; break;
        case '2' : (*characters)[i] = CHAR_2; break;
        case '3' : (*characters)[i] = CHAR_3; break;
        case '4' : (*characters)[i] = CHAR_4; break;
        case '5' : (*characters)[i] = CHAR_5; break;
        case '6' : (*characters)[i] = CHAR_6; break;
        case '7' : (*characters)[i] = CHAR_7; break;
        case '8' : (*characters)[i] = CHAR_8; break;
        case '9' : (*characters)[i] = CHAR_9; break;
        case '0' : (*characters)[i] = CHAR_0; break;
        case ' ' : (*characters)[i] = CHAR_SPACE; break;
        case '\n': (*characters)[i] = CHAR_NEWLINE; break;
        case ',' : (*characters)[i] = CHAR_COMMA; break;
        case '.' : (*characters)[i] = CHAR_DOT; break;
        case '-' : (*characters)[i] = CHAR_MINUS; break;
        case '+' : (*characters)[i] = CHAR_PLUS; break;
        case '_' : (*characters)[i] = CHAR_UNDERSCORE; break;
        case ':' : (*characters)[i] = CHAR_COLON; break;
        case ';' : (*characters)[i] = CHAR_SEMICOLON; break;
        case '!' : (*characters)[i] = CHAR_EXCLAMATION; break;
        case '?' : (*characters)[i] = CHAR_QUESTION; break;
        case '@' : (*characters)[i] = CHAR_AT; break;
        case '#' : (*characters)[i] = CHAR_HASH; break;
        case '$' : (*characters)[i] = CHAR_DOLLAR; break;
        case '%' : (*characters)[i] = CHAR_PERCENT; break;
        case '&' : (*characters)[i] = CHAR_AMPERSAND; break;
        case '/' : (*characters)[i] = CHAR_SLASH; break;
        case '(' : (*characters)[i] = CHAR_LPAREN; break;
        case ')' : (*characters)[i] = CHAR_RPAREN; break;
        case '=' : (*characters)[i] = CHAR_EQUAL; break;
        case '<' : (*characters)[i] = CHAR_LESS; break;
        case '>' : (*characters)[i] = CHAR_GREATER; break;
        case '|' : (*characters)[i] = CHAR_PIPE; break;
        case '\\': (*characters)[i] = CHAR_BACKSLASH; break;
        case '\'': (*characters)[i] = CHAR_APOSTROPHE; break;
        case '"' : (*characters)[i] = CHAR_QUOTE; break;
        default  : (*characters)[i] = CHAR_NONE; break;
        }
    }

    return RES_OK;
}

const char *character_names[] = {
    [CHAR_NONE]          = "CHAR_NONE",
    [CHAR_a]             = "CHAR_a",
    [CHAR_b]             = "CHAR_b",
    [CHAR_c]             = "CHAR_c",
    [CHAR_d]             = "CHAR_d",
    [CHAR_e]             = "CHAR_e",
    [CHAR_f]             = "CHAR_f",
    [CHAR_g]             = "CHAR_g",
    [CHAR_h]             = "CHAR_h",
    [CHAR_i]             = "CHAR_i",
    [CHAR_j]             = "CHAR_j",
    [CHAR_k]             = "CHAR_k",
    [CHAR_l]             = "CHAR_l",
    [CHAR_m]             = "CHAR_m",
    [CHAR_n]             = "CHAR_n",
    [CHAR_o]             = "CHAR_o",
    [CHAR_p]             = "CHAR_p",
    [CHAR_q]             = "CHAR_q",
    [CHAR_r]             = "CHAR_r",
    [CHAR_s]             = "CHAR_s",
    [CHAR_t]             = "CHAR_t",
    [CHAR_u]             = "CHAR_u",
    [CHAR_v]             = "CHAR_v",
    [CHAR_w]             = "CHAR_w",
    [CHAR_x]             = "CHAR_x",
    [CHAR_y]             = "CHAR_y",
    [CHAR_z]             = "CHAR_z",
    [CHAR_A]             = "CHAR_A",
    [CHAR_B]             = "CHAR_B",
    [CHAR_C]             = "CHAR_C",
    [CHAR_D]             = "CHAR_D",
    [CHAR_E]             = "CHAR_E",
    [CHAR_F]             = "CHAR_F",
    [CHAR_G]             = "CHAR_G",
    [CHAR_H]             = "CHAR_H",
    [CHAR_I]             = "CHAR_I",
    [CHAR_J]             = "CHAR_J",
    [CHAR_K]             = "CHAR_K",
    [CHAR_L]             = "CHAR_L",
    [CHAR_M]             = "CHAR_M",
    [CHAR_N]             = "CHAR_N",
    [CHAR_O]             = "CHAR_O",
    [CHAR_P]             = "CHAR_P",
    [CHAR_Q]             = "CHAR_Q",
    [CHAR_R]             = "CHAR_R",
    [CHAR_S]             = "CHAR_S",
    [CHAR_T]             = "CHAR_T",
    [CHAR_U]             = "CHAR_U",
    [CHAR_V]             = "CHAR_V",
    [CHAR_W]             = "CHAR_W",
    [CHAR_X]             = "CHAR_X",
    [CHAR_Y]             = "CHAR_Y",
    [CHAR_Z]             = "CHAR_Z",
    [CHAR_1]             = "CHAR_1",
    [CHAR_2]             = "CHAR_2",
    [CHAR_3]             = "CHAR_3",
    [CHAR_4]             = "CHAR_4",
    [CHAR_5]             = "CHAR_5",
    [CHAR_6]             = "CHAR_6",
    [CHAR_7]             = "CHAR_7",
    [CHAR_8]             = "CHAR_8",
    [CHAR_9]             = "CHAR_9",
    [CHAR_0]             = "CHAR_0",
    [CHAR_BACKSLASH]     = "CHAR_BACKSLASH",
    [CHAR_APOSTROPHE]    = "CHAR_APOSTROPHE",
    [CHAR_LEFT_ANGLE]    = "CHAR_LEFT_ANGLE",
    [CHAR_TAB]           = "CHAR_TAB",
    [CHAR_PLUS]          = "CHAR_PLUS",
    [CHAR_ACUTE]         = "CHAR_ACUTE",
    [CHAR_TILDE]         = "CHAR_TILDE",
    [CHAR_CEDILLA]       = "CHAR_CEDILLA",
    [CHAR_MOI]           = "CHAR_MOI",
    [CHAR_NEWLINE]       = "CHAR_NEWLINE",
    [CHAR_COMMA]         = "CHAR_COMMA",
    [CHAR_DOT]           = "CHAR_DOT",
    [CHAR_MINUS]         = "CHAR_MINUS",
    [CHAR_SPACE]         = "CHAR_SPACE",
    [CHAR_LESS]          = "CHAR_LESS",
    [CHAR_PIPE]          = "CHAR_PIPE",
    [CHAR_EXCLAMATION]   = "CHAR_EXCLAMATION",
    [CHAR_QUOTE]         = "CHAR_QUOTE",
    [CHAR_HASH]          = "CHAR_HASH",
    [CHAR_DOLLAR]        = "CHAR_DOLLAR",
    [CHAR_PERCENT]       = "CHAR_PERCENT",
    [CHAR_AMPERSAND]     = "CHAR_AMPERSAND",
    [CHAR_SLASH]         = "CHAR_SLASH",
    [CHAR_LPAREN]        = "CHAR_LPAREN",
    [CHAR_RPAREN]        = "CHAR_RPAREN",
    [CHAR_EQUAL]         = "CHAR_EQUAL",
    [CHAR_QUESTION]      = "CHAR_QUESTION",
    [CHAR_RIGHT_ANGLE]   = "CHAR_RIGHT_ANGLE",
    [CHAR_ASTERISK]      = "CHAR_ASTERISK",
    [CHAR_GRAVE]         = "CHAR_GRAVE",
    [CHAR_CIRCUMFLEX]    = "CHAR_CIRCUMFLEX",
    [CHAR_CEDILLA_UPPER] = "CHAR_CEDILLA_UPPER",
    [CHAR_FOI]           = "CHAR_FOI",
    [CHAR_SEMICOLON]     = "CHAR_SEMICOLON",
    [CHAR_COLON]         = "CHAR_COLON",
    [CHAR_UNDERSCORE]    = "CHAR_UNDERSCORE",
    [CHAR_GREATER]       = "CHAR_GREATER",
    [CHAR_AT]            = "CHAR_AT",
    [CHAR_POUND]         = "CHAR_POUND",
    [CHAR_SECTION]       = "CHAR_SECTION",
    [CHAR_EURO]          = "CHAR_EURO",
    [CHAR_LCURLY]        = "CHAR_LCURLY",
    [CHAR_LBRACKET]      = "CHAR_LBRACKET",
    [CHAR_RBRACKET]      = "CHAR_RBRACKET",
    [CHAR_RCURLY]        = "CHAR_RCURLY",
    [CHAR_TREMA]         = "CHAR_TREMA",
    [CHAR_a_ACUTE]       = "CHAR_a_ACUTE",
    [CHAR_a_GRAVE]       = "CHAR_a_GRAVE",
    [CHAR_a_CIRC]        = "CHAR_a_CIRC",
    [CHAR_a_TILDE]       = "CHAR_a_TILDE",
    [CHAR_a_UMLAUT]      = "CHAR_a_UMLAUT",
    [CHAR_a_RING]        = "CHAR_a_RING",
    [CHAR_e_ACUTE]       = "CHAR_e_ACUTE",
    [CHAR_e_GRAVE]       = "CHAR_e_GRAVE",
    [CHAR_e_CIRC]        = "CHAR_e_CIRC",
    [CHAR_e_UMLAUT]      = "CHAR_e_UMLAUT",
    [CHAR_i_ACUTE]       = "CHAR_i_ACUTE",
    [CHAR_i_GRAVE]       = "CHAR_i_GRAVE",
    [CHAR_i_CIRC]        = "CHAR_i_CIRC",
    [CHAR_i_UMLAUT]      = "CHAR_i_UMLAUT",
    [CHAR_o_ACUTE]       = "CHAR_o_ACUTE",
    [CHAR_o_GRAVE]       = "CHAR_o_GRAVE",
    [CHAR_o_CIRC]        = "CHAR_o_CIRC",
    [CHAR_o_TILDE]       = "CHAR_o_TILDE",
    [CHAR_o_UMLAUT]      = "CHAR_o_UMLAUT",
    [CHAR_u_ACUTE]       = "CHAR_u_ACUTE",
    [CHAR_u_GRAVE]       = "CHAR_u_GRAVE",
    [CHAR_u_CIRC]        = "CHAR_u_CIRC",
    [CHAR_u_UMLAUT]      = "CHAR_u_UMLAUT",
    [CHAR_A_ACUTE]       = "CHAR_A_ACUTE",
    [CHAR_A_GRAVE]       = "CHAR_A_GRAVE",
    [CHAR_A_CIRC]        = "CHAR_A_CIRC",
    [CHAR_A_TILDE]       = "CHAR_A_TILDE",
    [CHAR_A_UMLAUT]      = "CHAR_A_UMLAUT",
    [CHAR_A_RING]        = "CHAR_A_RING",
    [CHAR_E_ACUTE]       = "CHAR_E_ACUTE",
    [CHAR_E_GRAVE]       = "CHAR_E_GRAVE",
    [CHAR_E_CIRC]        = "CHAR_E_CIRC",
    [CHAR_E_UMLAUT]      = "CHAR_E_UMLAUT",
    [CHAR_I_ACUTE]       = "CHAR_I_ACUTE",
    [CHAR_I_GRAVE]       = "CHAR_I_GRAVE",
    [CHAR_I_CIRC]        = "CHAR_I_CIRC",
    [CHAR_I_UMLAUT]      = "CHAR_I_UMLAUT",
    [CHAR_O_ACUTE]       = "CHAR_O_ACUTE",
    [CHAR_O_GRAVE]       = "CHAR_O_GRAVE",
    [CHAR_O_CIRC]        = "CHAR_O_CIRC",
    [CHAR_O_TILDE]       = "CHAR_O_TILDE",
    [CHAR_O_UMLAUT]      = "CHAR_O_UMLAUT",
    [CHAR_U_ACUTE]       = "CHAR_U_ACUTE",
    [CHAR_U_GRAVE]       = "CHAR_U_GRAVE",
    [CHAR_U_CIRC]        = "CHAR_U_CIRC",
    [CHAR_U_UMLAUT]      = "CHAR_U_UMLAUT",
};
