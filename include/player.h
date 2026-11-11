#ifndef PLAYER_H
#define PLAYER_H

#include "types.h"
#include "config.h"

void move_player(Player *player, int (*map)[MAP_COLS]);
void extra_controls();
void controls(Player *player, int (*map)[MAP_COLS]);
//2. maybe randomize spawn on free location later idk

#endif