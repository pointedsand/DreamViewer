#ifndef MAP_H
#define MAP_H

#include "config.h"
#include "types.h"

void print_map(int (*map)[MAP_COLS]);
void draw_map(int (*map)[MAP_COLS]);
void draw_player(Player player);
void draw_raycasts(Player player, float ray_distances[NUM_RAYS]);
void print_ray_distances(float arr[NUM_RAYS]);

#endif