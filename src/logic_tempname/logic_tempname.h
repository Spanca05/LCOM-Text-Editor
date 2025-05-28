#ifndef _LOGIC_TEMPNAME_H_
#define _LOGIC_TEMPNAME_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/result.h"
#include "../utils/character.h"
#include "../utils/cursor-rato.h"
#include "../utils/kbd_modifier.h"

Result(scancode_to_character)(uint16_t scancode, Character *character);

Result(character_handler)(Character *character, Cursor *cursor, KBD_modifier *kbd_modifier);
Result(release_handler)(Character *character, Cursor *cursor, KBD_modifier *kbd_modifier, bool *running);

bool is_drawable(Character character);
bool (is_kbd_modifier)(Character character);
bool (is_arrow)(Character character);

Result(character_to_caps)(Character *character);
Result(character_from_caps)(Character *character);

Result(insert_into_buffer)(char *buffer, Character character);
Result(delete_from_buffer)(char *buffer, int pos);

Result(update_cursor)(Cursor *cursor, Character character);
Result(press_kbd_modifier)(KBD_modifier *kbd_modifier, Character character);
Result(release_kbd_modifier)(KBD_modifier *kbd_modifier, Character character);

#endif
