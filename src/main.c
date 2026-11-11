#include <stdlib.h>
#include <raylib.h>
#include "config.h"
#include "debug.h"
#include "map.h"
#include "player.h"
#include "raycast.h"
#include "renderer.h"
#include "types.h"

int main()
{

    //int map[MAP_ROWS][MAP_COLS];
    //init_map(map);
    int map[MAP_ROWS][MAP_COLS] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1},
    {1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1},
    {1,0,1,1,0,1,1,0,0,0,1,1,1,1,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1},
    {1,0,0,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,1,0,0,0,0,0,1,0,1,1,1,0,0,0,1},
    {1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,0,0,1},
    {1,0,1,1,0,0,0,0,0,1,0,1,1,1,0,1,0,0,0,1},
    {1,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
    {1,0,0,1,0,1,1,1,0,0,0,1,0,0,1,1,1,0,0,1},
    {1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1},
    {1,0,1,1,1,0,0,1,0,1,1,1,0,0,1,0,0,1,0,1},
    {1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1},
    {1,0,0,0,1,1,1,0,0,1,0,1,0,1,1,1,0,1,0,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
    print_map(map);

    Player player = {5.5, 5.5, 0};

    float ray_distances[NUM_RAYS];

    InitWindow(1920, 1080, "DREAMVIEWER");

    while(!WindowShouldClose())
    {
        //move_player(&player, map);
        //extra_controls();
        controls(&player, map);
        raycast(map, player, ray_distances);
        BeginDrawing();
        ClearBackground(BLACK);
        //draw_map(map);
        //draw_player(player);
        //draw_raycasts(player, ray_distances);
        render_view(player, ray_distances);
        EndDrawing();
    }
    //test one ray
    //float distance = cast_ray(map, player, player.angle); 
    //printf("Hit distance: %f\n", distance);

    CloseWindow();

    return EXIT_SUCCESS;
}