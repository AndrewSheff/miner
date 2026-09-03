#ifndef COLLECTIONS_H
#define COLLECTIONS_H

#include "ncursescustom.h"
#include "prop.h"
#include "building.h"
#include "enums.h"
#include "environments.h"

#define PROP_TYPE_COUNT 3
#define BUILDING_TYPE_COUNT 5

/* prop collections */
struct prop_array ore_array;
struct prop_array ingot_array;
struct prop_array production_array;

struct prop_array prop_collection[PROP_TYPE_COUNT];
chtype pchar_collection[PROP_TYPE_COUNT];
chtype native_building_char[PROP_TYPE_COUNT];
chtype dest_building_char[PROP_TYPE_COUNT];
chtype out_direction[PROP_TYPE_COUNT];

/* building collections */
struct building_array miner_array;
struct building_array furnace_array;
struct building_array assembler_array;

struct building_array building_collection[BUILDING_TYPE_COUNT];
chtype bchar_collection[BUILDING_TYPE_COUNT];
int produce_time[BUILDING_TYPE_COUNT];
bool can_process[BUILDING_TYPE_COUNT];

/* mappers */
enum prop_type building_to_prop[BUILDING_TYPE_COUNT];
enum building_type prop_to_building[PROP_TYPE_COUNT];
enum building_type key_to_building[255];

bool cant_build_on[255];

void init_prop_collections();
void init_building_collections();
void init_mappers();
void init_can_built_on();
void init_collections();

#endif