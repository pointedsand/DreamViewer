#include <stdlib.h>
#include <math.h>
#include <raylib.h>
#include "raycast.h"

float cast_ray(int (*map)[MAP_COLS], Player player, float angle)
{
    if(!map)
    {
        return NAN;
    }

    //ray direction; angle -> unit vector
    float x_dir = cosf(angle);
    float y_dir = sinf(angle);

    //map cell where ray originates
    int map_x = (int)player.x; 
    int map_y = (int)player.y;

    //direction to move through cells after crossing boundary
    int cell_step_x;
    int cell_step_y;

    if(x_dir < 0) {cell_step_x = -1;} else {cell_step_x = 1;}
    if(y_dir < 0) {cell_step_y = -1;} else {cell_step_y = 1;}

    //find first grid boundaries in ray direction
    int first_x_boundary = map_x;
    int first_y_boundary = map_y;

    if(cell_step_x == 1) {first_x_boundary += 1;} //map_x + 1 = boundary on positive (right) side of the cell
    if(cell_step_y == 1) {first_y_boundary += 1;}

    //coordinate change required to reach first boundaries
    float delta_x = first_x_boundary - player.x;
    float delta_y = first_y_boundary - player.y;

    float dist_to_x_boundary; //distance from player to next x boundary
    float x_boundary_increment; //distance along ray between every boundary
    if (x_dir == 0) 
    { 
        dist_to_x_boundary = x_boundary_increment = INFINITY; //handle divide by 0 error
    } 
    else 
    { 
        dist_to_x_boundary = delta_x / x_dir; 
        x_boundary_increment = 1.0f / fabsf(x_dir); 
    }

    float dist_to_y_boundary;
    float y_boundary_increment;
    if (y_dir == 0) 
    { 
        dist_to_y_boundary = y_boundary_increment = INFINITY; 
    }
    else 
    { 
        dist_to_y_boundary = delta_y / y_dir; 
        y_boundary_increment = 1.0f / fabsf(y_dir); 
    }


    //loop
    float hit_distance;
    while(1) 
    {
        if(dist_to_x_boundary > dist_to_y_boundary) 
        {
            map_y += cell_step_y;
            hit_distance = dist_to_y_boundary;
            dist_to_y_boundary += y_boundary_increment;
        }
        else
        {
            map_x += cell_step_x;
            hit_distance = dist_to_x_boundary;
            dist_to_x_boundary += x_boundary_increment;
        }

        if (map[map_y][map_x] != 0) 
        {
            break;
        }
    }
    return hit_distance;
}

int raycast(int (*map)[MAP_COLS], Player player, float ray_distances[NUM_RAYS])  
{
    if(!map)
    {
        return EXIT_FAILURE;
    }

    float working_angle = player.angle - PI/6;
    float angle_increment = (PI/3)/(NUM_RAYS - 1);

    for(int i = 0; i < NUM_RAYS; i++)
    {
        ray_distances[i] = cast_ray(map, player, working_angle);

        working_angle += angle_increment;
    }
    
    return EXIT_SUCCESS;
}
