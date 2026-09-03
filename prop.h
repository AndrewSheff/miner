#ifndef PROP_H
#define PROP_H

#include <time.h>
#include "ncursescustom.h"
#include "enums.h"

struct prop
{
    struct timespec ts;
    struct coordinates coord;
    chtype cur_char;
    enum prop_type p_type;
};

struct prop_array
{
    struct prop *array;
    int props_count;
};

void create_prop(struct coordinates coord, enum prop_type p_type);
void delete_prop(int p_index, struct prop_array *p_array);
void prop_cycler();

#endif