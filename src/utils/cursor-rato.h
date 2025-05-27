#ifndef CURSOR_H
#define CURSOR_H

#include <stdbool.h>

typedef struct {
    int cx;
    int cy;
    bool visible;
} Cursor;

typedef struct {
    int rx;
    int ry;
    bool pressed;
} Rato;


#endif
