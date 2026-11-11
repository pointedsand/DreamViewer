#include "map.h"

void init_map(int (*map)[MAP_COLS])
{
    for(int i = 0; i < MAP_ROWS; i++)
    {
        for(int j = 0; j < MAP_COLS; j++)
        {
            if((i == 0 || j == 0) || (i == MAP_ROWS-1 || j == MAP_COLS-1)) {map[i][j] = 1;}
            else{map[i][j] = 0;}
        }
    }
}