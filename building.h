#ifndef BUILDING_H
#define BUILDING_H

#include <time.h>
#include "ncursescustom.h"
#include "enums.h"
#include "environments.h"

struct building
{
    struct timespec ts;
    struct coordinates coord;
    enum building_type b_type;
    int prop_count;
};

struct building_array
{
    struct coordinates *array;
    int buildings_count;
};

struct building building_map[M_HEIGHT][M_WIDTH];

void create_building(struct coordinates coord, enum building_type b_type);
void delete_building(struct coordinates coord, struct building_array *b_array);
struct building *get_building_from_coord(struct coordinates coord);
void building_cycler();

#endif