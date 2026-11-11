#ifndef RAYCAST_H
#define RAYCAST_H

#include "config.h"
#include "types.h"
#include "map.h"

float cast_ray(int (*map)[MAP_COLS], Player player, float angle); //needs to return a RayHit obj, later though
int raycast(int (*map)[MAP_COLS], Player player, float ray_distances[NUM_RAYS]);

#endif