#include <stdio.h>
#include <math.h>
#include <raylib.h>
#include "debug.h"

void print_map(int (*map)[MAP_COLS])
{
    for(int i = 0; i < MAP_ROWS; i++)
    {
        for(int j = 0; j < MAP_COLS; j++)
        {
            printf("%d", map[i][j]);
        }
        printf("\n");
    }
}

void draw_map(int (*map)[MAP_COLS])
{
    for(int i = 0; i < MAP_ROWS; i++)
    {
        for(int j = 0; j < MAP_COLS; j++)
        {
            Color color = GREEN;
            int y_scaled = i * CELL_SIZE;
            int x_scaled = j * CELL_SIZE;
            if(map[i][j] == 1)
            {
                color = BLUE;
            }
            DrawRectangle(x_scaled, y_scaled, CELL_SIZE, CELL_SIZE, color);
        }
    }
}

void draw_player(Player player)
{
    float x_pos = player.x * CELL_SIZE;
    float y_pos = player.y * CELL_SIZE;
    float player_radius = CELL_SIZE/8;

    DrawCircle(x_pos, y_pos, player_radius, PURPLE);
    DrawLine(x_pos, y_pos, x_pos + 25*cosf(player.angle), y_pos + 25*sinf(player.angle), WHITE);
}

void draw_raycasts(Player player, float ray_distances[NUM_RAYS])
{
    float x_pos = player.x * CELL_SIZE;
    float y_pos = player.y * CELL_SIZE;

    float ray_angle = player.angle - PI/6;
    float angle_increment = (PI/3) / (NUM_RAYS - 1);

    for(int i = 0; i < NUM_RAYS; i++) 
    {
        float ray_pixel_length = ray_distances[i] * CELL_SIZE;
        float end_x = x_pos + cosf(ray_angle) * ray_pixel_length;
        float end_y = y_pos + sinf(ray_angle) * ray_pixel_length;

        DrawLine(
            x_pos, y_pos,
            end_x, end_y,
            BLACK
        );

        ray_angle += angle_increment;
    }
}

void print_ray_distances(float arr[NUM_RAYS]) 
{
    for(int i = 0; i < NUM_RAYS; i++) 
    {
        printf("arr[%d] = %f\n", i, arr[i]);
    }
}