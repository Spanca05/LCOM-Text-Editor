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

Result(scancode_to_character)(uint16_t scancode, Character *character);
Result(character_to_caps)(Character *character);
Result(character_from_caps)(Character *character);
bool is_drawable(Character character);
Result(insert_into_buffer)(char *buffer, Character character);
Result(delete_from_buffer)(char *buffer, int pos);
Result(update_cursor)(Cursor cursor, Character character);


Result(character_processor)(Character character); // Not implemented!


#endif
