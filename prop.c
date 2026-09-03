#include <stdlib.h>
#include "prop.h"
#include "building.h"
#include "collections.h"

struct prop_array ore_array = {.props_count=0};
struct prop_array ingot_array = {.props_count=0};
struct prop_array production_array = {.props_count=0};

void create_prop(struct coordinates coord, enum prop_type p_type)
{
    struct prop new_prop = {.coord = coord, .cur_char = p_type, .p_type = p_type};
    clock_gettime(CLOCK_REALTIME, &(new_prop.ts));
    struct prop_array *p_array = &prop_collection[p_type];
    p_array->props_count++;
    p_array->array = realloc(p_array->array, p_array->props_count*sizeof(struct prop));
    p_array->array[p_array->props_count-1] = new_prop;
}

void delete_prop(int p_index, struct prop_array *p_array)
{
    for (int i = p_index; i < p_array->props_count-1; i++)
    {
        p_array->array[i] = p_array->array[i+1];
    }
    p_array->props_count--;
    p_array->array = realloc(p_array->array, p_array->props_count*sizeof(struct prop));
}

void prop_cycler()
{
    for (int a_i = 0; a_i < PROP_TYPE_COUNT; a_i++)
    {
        struct prop_array *p_array = &prop_collection[a_i];
        if (p_array->props_count==0) {
            continue;
        }
        int props_to_delete[p_array->props_count];
        int props_to_delete_i = 0;
        for (int i = 0; i < p_array->props_count; i++)
        {
            struct prop *cur_prop = &p_array->array[i];
            struct timespec ts_now;
            clock_gettime(CLOCK_REALTIME, &ts_now);
            if (ts_now.tv_nsec >= (cur_prop->ts.tv_nsec)
                && ts_now.tv_sec-(cur_prop->ts.tv_sec)>= move_time)
            {
                struct coordinates next_coord;
                if (cur_prop->cur_char == cur_prop->p_type) 
                {
                    next_coord = arrowmove(out_direction[cur_prop->p_type], cur_prop->coord);
                    cur_prop->cur_char = native_building_char[cur_prop->p_type];
                }
                else
                {
                    next_coord = arrowmove(cur_prop->cur_char, cur_prop->coord);
                }
                chtype next_char = winch(stdscr);
                if (next_char == ACS_UARROW || next_char == ACS_DARROW || next_char == ACS_LARROW || next_char == ACS_RARROW)
                {
                    addch(pchar_collection[cur_prop->p_type]);
                    mvaddch(cur_prop->coord.y, cur_prop->coord.x, cur_prop->cur_char);
                    cur_prop->coord = next_coord;
                    cur_prop->cur_char = next_char;
                } else if (next_char == dest_building_char[cur_prop->p_type]){
                    building_map[next_coord.y][next_coord.x].prop_count++;
                    mvaddch(cur_prop->coord.y, cur_prop->coord.x, cur_prop->cur_char);
                    props_to_delete[props_to_delete_i] = i;
                    props_to_delete_i++;
                }
                cur_prop->ts = ts_now;
            }
        }
        for (int i = props_to_delete_i-1; i >= 0; i--)
        {
            delete_prop(props_to_delete[i], p_array);
        }
    }
}

