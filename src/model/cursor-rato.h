#ifndef CURSOR_H
#define CURSOR_H

#include <stdbool.h>

typedef struct Cursor {
    int  cx;
    int  cy;
    int  counter;
    bool visible;
} Cursor;

typedef struct Rato {
    int  rx;
    int  ry;
    bool pressed;
} Rato;


#endif
