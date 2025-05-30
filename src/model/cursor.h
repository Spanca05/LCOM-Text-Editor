#ifndef CURSOR_H
#define CURSOR_H

#include <stdbool.h>

#include "../utils/result.h"
#include "key.h"

typedef struct Cursor {
    uint64_t column;
    uint64_t line;
    uint64_t counter;
    bool     visible;
} Cursor;

void tick_cursor(Cursor *cursor);

#endif // CURSOR_H
