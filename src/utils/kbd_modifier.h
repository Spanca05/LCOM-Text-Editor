#ifndef KBD_MODIFIER_H
#define KBD_MODIFIER_H

#include <stdbool.h>

typedef struct {
    bool shift;         // True if either shift is pressed
    bool ctrl;          // True if either ctrl is pressed
    bool lalt;          // True if Left Alt
    bool ralt;          // True if Right Alt
    bool caps_lock;     // True if Caps Lock
    
    // Uncomment if we need this:
    //bool scroll_lock;   // Scroll Lock
    // bool num_lock;      // Num Lock
    // bool lgui;       // Left GUI (Windows/Command)
    // bool rgui;       // Right GUI (Windows/Command)
} KBD_modifier;

#endif
