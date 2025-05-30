#ifndef BUFFER_H
#define BUFFER_H

#include "../model/character.h"

void init_buffer();

void   tick_cursor();
Result update_cursor(Key key);

void add_character_to_buffer(Character character);

// Debug
// TODO Delete when not needed
void print_buffer_state(Modifiers modifiers);

#endif // BUFFER_H
