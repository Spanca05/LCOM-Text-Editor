#ifndef CURSOR_H
#define CURSOR_H

#include <stdbool.h>

#include "../utils/result.h"
#include "key.h"

typedef struct Cursor {
    int  column;
    int  line;
    int  counter;
    bool visible;
} Cursor;

void tick_cursor(Cursor *cursor);

#endif // CURSOR_H
