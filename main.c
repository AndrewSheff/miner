#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include "ncursescustom.h"
#include "building.h"
#include "prop.h"
#include "collections.h"


struct coordinates cursor = {0,0};

bool belt_mode = FALSE;

time_t start_time;

void dmove(chtype yk, chtype xk)
{
    int y = cursor.y, x = cursor.y;
    if (yk != KEY_LEFT && yk != KEY_RIGHT)
    {
        yk == KEY_DOWN ? y++ : y--;
    }
    if (xk != KEY_UP && xk != KEY_DOWN)
    {
        xk == KEY_LEFT ? x-- : x++;
    }
    move(y, x);
}

struct coordinates arrowmove(chtype arrow, struct coordinates p_coord) 
{
    struct coordinates coord = {p_coord.y, p_coord.x};
    if (arrow != ACS_LARROW && arrow != ACS_RARROW)
    {
        arrow == ACS_DARROW ? coord.y++ : coord.y--;
    }
    if (arrow != ACS_UARROW && arrow != ACS_DARROW)
    {
        arrow == ACS_LARROW ? coord.x-- : coord.x++;
    }
    move(coord.y, coord.x);
    return coord;
}

void move_cursor(chtype res)
{
    mvaddch(cursor.y,cursor.x, (winch(stdscr) & ~A_REVERSE));
    if (res == 'w' || res == KEY_UP)
        cursor.y--;
    else if (res == 's' || res == KEY_DOWN)
        cursor.y++;
    else if (res == 'a' || res == KEY_LEFT)
        cursor.x--;
    else if (res == 'd' || res == KEY_RIGHT)
        cursor.x++;
    mvaddch(cursor.y,cursor.x, (winch(stdscr) | A_REVERSE));
}

void delete_entities(struct coordinates coord)
{
    struct building *c_building = get_building_from_coord(coord);
    if (c_building->b_type != EMPTY)
    {
        delete_building(coord, &building_collection[c_building->b_type]);

        struct prop_array *p_array = &prop_collection[building_to_prop[c_building->b_type]];
        int props_to_delete[p_array->props_count];
        int props_to_delete_i = 0;
        for (int i = 0; i < p_array->props_count; i++)
        {
            if (p_array->array[i].coord.y == coord.y && p_array->array[i].coord.x == coord.x)
            {
                props_to_delete[props_to_delete_i] = i;
                props_to_delete_i++;
            }
        }
        for (int i = props_to_delete_i-1; i >= 0; i--)
        {
            delete_prop(props_to_delete[i], p_array);
        }
    }
    else
    {
        for (int a_i = 0; a_i < PROP_TYPE_COUNT; a_i++)
        {
            struct prop_array *p_array = &prop_collection[a_i];
            for (int i = 0; i < p_array->props_count; i++)
            {
                if (p_array->array[i].coord.y == coord.y && p_array->array[i].coord.x == coord.x)
                {
                    delete_prop(i, p_array);
                    return;
                }
            }
        }
    }
}

int process_input()
{
    chtype res = getch();
    if (res == K_EXIT)
    {
        return 1;
    }
    if (res == K_BELT_MODE)
    {
        belt_mode = !belt_mode;
    }
    else if (belt_mode)
    {
        //стрелочки на клаве
        if (res >= 258 && res <= 261) 
        {
            move(cursor.y, cursor.x);
            chtype cur_char = (winch(stdscr) & A_CHARTEXT);
            if (!cant_build_on[cur_char]) 
            {
                switch (res)
                {
                    case KEY_UP:
                        addch(ACS_UARROW);
                        break;
                    case KEY_DOWN:
                        addch(ACS_DARROW);
                        break;
                    case KEY_LEFT:
                        addch(ACS_LARROW);
                        break;
                    case KEY_RIGHT:
                        addch(ACS_RARROW);
                        break;
                }
            }
            move_cursor(res);
        }
    }
    else if (res==K_MOVE_UP || res==K_MOVE_DOWN || res==K_MOVE_LEFT || res==K_MOVE_RIGHT) 
    {
        move_cursor(res);
    }
    else if (res == K_MINER || res == K_FURNACE || res == K_ASSEMBLER)
    {
        chtype cur_char = (winch(stdscr) & A_CHARTEXT);
        if (!cant_build_on[cur_char])
        {
            enum building_type b_type = key_to_building[res];
            create_building(cursor, b_type);
            mvaddch(cursor.y,cursor.x, bchar_collection[b_type]);
        }
    }
    else if (res == K_REMOVE)
    {
        mvaddch(cursor.y,cursor.x, EMPTY_FIELD_CH);
        delete_entities(cursor);
    }
    return 0;
}

int main(int argc,char *argv[])
{
    start_time = time(NULL);
    setlocale(LC_ALL, "");
    initscr();


    int row, col;
    getmaxyx(stdscr, row, col);

    curs_set(0);
    noecho();
    cbreak();
    nodelay(stdscr, true);
    keypad(stdscr, true);

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLUE);

    init_collections();

    //отрисовка поля
    for (int i = 0; i<M_HEIGHT;i++) 
    {
        for (int j = 0; j<M_WIDTH;j++) 
        {
            mvaddch(i,j,EMPTY_FIELD_CH);
        }
    }

    refresh();

    while (true)
    {
        if (process_input() == 1)
        {
            break;
        }
        prop_cycler();
        building_cycler();
        refresh();
    }
    for (int a_i = 0; a_i < PROP_TYPE_COUNT; a_i++)
    {
        free(prop_collection[a_i].array);
    }
    for (int a_i = 0; a_i < BUILDING_TYPE_COUNT; a_i++)
    {
        free(building_collection[a_i].array);
    }
    endwin(); // завершение работы с ncurses
}