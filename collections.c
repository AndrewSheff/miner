#include "collections.h"

void init_prop_collections()
{
    prop_collection[ORE] = ore_array;
    prop_collection[INGOT] = ingot_array;
    prop_collection[PRODUCTION] = production_array;

    pchar_collection[ORE] = '*';
    pchar_collection[INGOT] = '#';
    pchar_collection[PRODUCTION] = '+';

    native_building_char[ORE] = 'M';
    native_building_char[INGOT] = 'F';
    native_building_char[PRODUCTION] = 'A';

    dest_building_char[ORE] = 'F';
    dest_building_char[INGOT] = 'A';
    dest_building_char[PRODUCTION] = 'H';

    out_direction[ORE] = ACS_UARROW;
    out_direction[INGOT] = ACS_RARROW;
    out_direction[PRODUCTION] = ACS_DARROW;
}

void init_building_collections()
{
    building_collection[MINER] = miner_array;
    building_collection[FURNACE] = furnace_array;
    building_collection[ASSEMBLER] = assembler_array;

    bchar_collection[MINER] = 'M';
    bchar_collection[FURNACE] = 'F';
    bchar_collection[ASSEMBLER] = 'A';

    can_process[MINER] = false;
    can_process[FURNACE] = true;
    can_process[ASSEMBLER] = true;

    produce_time[MINER] = miner_process_time;
    produce_time[FURNACE] = furnace_process_time;
    produce_time[ASSEMBLER] = assembler_process_time;
}

void init_mappers()
{
    building_to_prop[MINER] = ORE;
    building_to_prop[FURNACE] = INGOT;
    building_to_prop[ASSEMBLER] = PRODUCTION;

    prop_to_building[ORE] = MINER;
    prop_to_building[INGOT] = FURNACE;
    prop_to_building[PRODUCTION] = ASSEMBLER;

    key_to_building[K_MINER] = MINER;
    key_to_building[K_FURNACE] = FURNACE;
    key_to_building[K_ASSEMBLER] = ASSEMBLER;
}

void init_can_built_on()
{
    cant_build_on[pchar_collection[ORE]] = true;
    cant_build_on[pchar_collection[INGOT]] = true;
    cant_build_on[pchar_collection[PRODUCTION]] = true;

    cant_build_on[bchar_collection[MINER]] = true;
    cant_build_on[bchar_collection[FURNACE]] = true;
    cant_build_on[bchar_collection[ASSEMBLER]] = true;
    cant_build_on[bchar_collection[HUB]] = true;
}

void init_collections()
{
    init_prop_collections();
    init_building_collections();
    init_mappers();
    init_can_built_on();
}