#ifndef NCURSESCUSTOM_H
#define NCURSESCUSTOM_H

#include <ncurses.h>

struct coordinates {
    int y;
    int x;
};

void dmove(chtype yk, chtype xk);
struct coordinates arrowmove(chtype arrow, struct coordinates p_coord);

#endif