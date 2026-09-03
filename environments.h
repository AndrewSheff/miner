#ifndef ENVIRONMENTS_H
#define ENVIRONMENTS_H

#define K_EXIT          'q'
#define K_BELT_MODE     'b'
#define K_REMOVE        'r'
#define K_MINER         '1'
#define K_FURNACE       '2'
#define K_ASSEMBLER     '3'
#define K_MOVE_UP       'w'
#define K_MOVE_DOWN     's'
#define K_MOVE_LEFT     'a'
#define K_MOVE_RIGHT    'd'

#define EMPTY_FIELD_CH (' ' | COLOR_PAIR(1))

#define M_HEIGHT 20
#define M_WIDTH 40

int move_time;
int miner_process_time;
int furnace_process_time;
int assembler_process_time;

#endif