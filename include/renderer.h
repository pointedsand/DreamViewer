#ifndef RENDERER_H
#define RENDERER_H

#include "types.h"
#include "config.h"

char get_wall_character(float distance); //make this more generic later + use array with distance -> index hash
void draw_floor(); //cooked rn, needs a lot of work aka FLOORCASTING T-T
void render_view(Player player, float ray_distances[NUM_RAYS]);

#endif