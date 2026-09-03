#include <stdlib.h>
#include "building.h"
#include "collections.h"

struct building_array miner_array = {.buildings_count=0};
struct building_array furnace_array = {.buildings_count=0};
struct building_array assembler_array = {.buildings_count=0};

struct building building_map[M_HEIGHT][M_WIDTH];

void create_building(struct coordinates coord, enum building_type b_type)
{
    struct building new_building = {.coord = coord, .b_type = b_type, .prop_count = 0};
    clock_gettime(CLOCK_REALTIME, &(new_building.ts));
    building_map[coord.y][coord.x] = new_building;
    struct building_array *b_array = &building_collection[b_type];
    b_array->buildings_count++;
    b_array->array = realloc(b_array->array, b_array->buildings_count*sizeof(struct coordinates));
    b_array->array[b_array->buildings_count-1] = coord;
}

void delete_building(struct coordinates coord, struct building_array *b_array)
{
    if (building_map[coord.y][coord.x].b_type == EMPTY)
    {
        return;
    }
    for (int i=0; i < b_array->buildings_count; i++)
    {
        struct coordinates cur_coord = b_array->array[i];
        if (cur_coord.y == coord.y && cur_coord.x == coord.x)
        {
            b_array->array[i] = b_array->array[b_array->buildings_count-1];
            b_array->buildings_count--;
            b_array->array = realloc(b_array->array, b_array->buildings_count*sizeof(struct coordinates));
            building_map[coord.y][coord.x].b_type = EMPTY;
            return;
        }
    }
}

struct building *get_building_from_coord(struct coordinates coord)
{
    return &building_map[coord.y][coord.x];
}

void building_cycler()
{
    for (int b_i=1; b_i < BUILDING_TYPE_COUNT; b_i++)
    {
        struct building_array *b_array = &building_collection[b_i];
        if (b_array->buildings_count==0) {
            continue;
        }
        for (int i = 0; i<b_array->buildings_count; i++)
        {
            struct building *cur_building = get_building_from_coord(b_array->array[i]);
            if ((can_process[cur_building->b_type] && cur_building->prop_count!=0) || !can_process[cur_building->b_type])
            {
                struct timespec ts_now;
                clock_gettime(CLOCK_REALTIME, &ts_now);
                if (ts_now.tv_nsec >= (cur_building->ts.tv_nsec)
                    && ts_now.tv_sec-(cur_building->ts.tv_sec)>= produce_time[cur_building->b_type])
                {
                    create_prop(cur_building->coord, building_to_prop[cur_building->b_type]);
                    clock_gettime(CLOCK_REALTIME, &(cur_building->ts));
                    if (can_process[cur_building->b_type])
                    {
                        cur_building->prop_count--;
                    }
                }
            }
        }
    }
}