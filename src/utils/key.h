#ifndef KEY_H
#define KEY_H

#include <stdbool.h>
#include <stdint.h>

#include "result.h"

// Enum for every physical key with a scancode (standard 104/105-key PC keyboard)
typedef enum {
    KEY_NONE = 0,    // No key pressed

    KEY_a,           // 'a' key
    KEY_b,           // 'b' key
    KEY_c,           // 'c' key
    KEY_d,           // 'd' key
    KEY_e,           // 'e' key
    KEY_f,           // 'f' key
    KEY_g,           // 'g' key
    KEY_h,           // 'h' key
    KEY_i,           // 'i' key
    KEY_j,           // 'j' key
    KEY_k,           // 'k' key
    KEY_l,           // 'l' key
    KEY_m,           // 'm' key
    KEY_n,           // 'n' key
    KEY_o,           // 'o' key
    KEY_p,           // 'p' key
    KEY_q,           // 'q' key
    KEY_r,           // 'r' key
    KEY_s,           // 's' key
    KEY_t,           // 't' key
    KEY_u,           // 'u' key
    KEY_v,           // 'v' key
    KEY_w,           // 'w' key
    KEY_x,           // 'x' key
    KEY_y,           // 'y' key
    KEY_z,           // 'z' key
    KEY_CEDILLA,     // 'ç' key
    KEY_ORDINAL,     // 'º' KEY


    KEY_1,           // '1' key
    KEY_2,           // '2' key
    KEY_3,           // '3' key
    KEY_4,           // '4' key
    KEY_5,           // '5' key
    KEY_6,           // '6' key
    KEY_7,           // '7' key
    KEY_8,           // '8' key
    KEY_9,           // '9' key
    KEY_0,           // '0' key


    KEY_F1,          // Function key F1
    KEY_F2,          // Function key F2
    KEY_F3,          // Function key F3
    KEY_F4,          // Function key F4
    KEY_F5,          // Function key F5
    KEY_F6,          // Function key F6
    KEY_F7,          // Function key F7
    KEY_F8,          // Function key F8
    KEY_F9,          // Function key F9
    KEY_F10,         // Function key F10
    KEY_F11,         // Function key F11
    KEY_F12,         // Function key F12


    KEY_ESC,         // Escape key
    KEY_INSERT,      // Insert key
    KEY_DELETE,      // Delete key
    KEY_BACKSPACE,   // Backspace key
    KEY_ENTER,       // Enter key
    KEY_TAB,         // Tab key
    KEY_SPACE,       // Spacebar key


    KEY_BACKSLASH,   // '\\' key
    KEY_APOSTROPHE,  // ''' key
    KEY_QUOTE,       // '«' key
    KEY_PLUS,        // '+' key
    KEY_ACCENT,      // '´' key
    KEY_TILL,        // '~' key
    KEY_ANGLE,       // '<' key
    KEY_COMMA,       // ',' key
    KEY_DOT,         // '.' key
    KEY_MINUS,       // '-' key


    KEY_ARROW_UP,    // Up Arrow key
    KEY_ARROW_DOWN,  // Down Arrow key
    KEY_ARROW_LEFT,  // Left Arrow key
    KEY_ARROW_RIGHT, // Right Arrow key


    KEY_MENU,        // Menu key
    KEY_HOME,        // Home key
    KEY_END,         // End key
    KEY_PAGEUP,      // Page Up key
    KEY_PAGEDOWN,    // Page Down key


    KEY_CAPSLOCK,    // Caps Lock key
    KEY_LSHIFT,      // Left Shift key
    KEY_RSHIFT,      // Right Shift key
    KEY_LCTRL,       // Left Ctrl key
    KEY_RCTRL,       // Right Ctrl key
    KEY_LALT,        // Left Alt key
    KEY_RALT,        // Right Alt key
    KEY_LGUI,        // Left GUI (Windows/Command) key
    KEY_RGUI,        // Right GUI (Windows/Command) key
} Key;

extern const char *key_names[];

Result(scancode_to_key)(uint16_t scancode, Key *key, bool *isPressCode);


#endif // KEY_H
