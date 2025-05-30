#include "cursor.h"
#include "../utils/result.h"
#include "key.h"

void tick_cursor(Cursor *cursor) {
    cursor->counter--;
    if (cursor->counter <= 0) {
        cursor->counter  = 30;
        cursor->visible ^= 1;
    }
}
