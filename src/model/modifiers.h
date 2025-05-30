#ifndef MODIFIER_H
#define MODIFIER_H

#include <stdbool.h>

typedef enum TextModifier {
    TEXT_MOD_NONE,
    TEXT_MOD_ACUTE_ACCENT,
    TEXT_MOD_GRAVE_ACCENT,
    TEXT_MOD_TILL_ACCENT,
    TEXT_MOD_CIRCUMFLEX_ACCENT,
    TEXT_MOD_UMLAUT
} TextModifier;

typedef struct Modifiers {
    bool ctrl;      // True if either ctrl is pressed
    bool shift;     // True if either shift is pressed
    bool lalt;      // True if Left Alt
    bool ralt;      // True if Right Alt
    bool caps_lock; // True if Caps Lock

    TextModifier textModifier;
} Modifiers;

static const char *text_modifier_names[] = {
    [TEXT_MOD_NONE] = "None",
    [TEXT_MOD_ACUTE_ACCENT] = "Acute Accent",
    [TEXT_MOD_GRAVE_ACCENT] = "Grave Accent",
    [TEXT_MOD_TILL_ACCENT] = "Tilde Accent",
    [TEXT_MOD_CIRCUMFLEX_ACCENT] = "Circumflex Accent",
    [TEXT_MOD_UMLAUT] = "Umlaut"
};
#endif // MODIFIER_H
