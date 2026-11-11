#include <math.h>
#include <raylib.h>
#include "player.h"
#include <config.h>
#include <stdio.h>

void move_player(Player *player, int (*map)[MAP_COLS]) 
{
    float move_speed = 2.0;
    float turn_speed = 2.0;

    float delta_t = GetFrameTime();

    if(IsKeyDown(KEY_W))
    {
        int next_x = player->x + cosf(player->angle) * move_speed * delta_t;
        int next_y = player->y + sinf(player->angle) * move_speed * delta_t;

        if(map[next_y][next_x] != 1)  //collision check
        {
            player->x += cosf(player->angle) * move_speed * delta_t;
            player->y += sinf(player->angle) * move_speed * delta_t;
        }
    }
        if(IsKeyDown(KEY_S))
    {
        int next_x = player->x - cosf(player->angle) * move_speed * delta_t;
        int next_y = player->y - cosf(player->angle) * move_speed * delta_t;

        if(map[next_y][next_x] != 1)  //collision check
        {
            player->x -= cosf(player->angle) * move_speed * delta_t;
            player->y -= sinf(player->angle) * move_speed * delta_t;
        }
    }
    if(IsKeyDown(KEY_A))
    {
        player->angle -= turn_speed * delta_t;
    }
    if(IsKeyDown(KEY_D))
    {
        player->angle += turn_speed * delta_t;
    }

    if(IsKeyPressed(KEY_Q)) 
    {
        float x_int = (player->x);
        float y_int = (player->y);
        printf("\n\nx: %f y: %f\n\n", x_int, y_int);
    }
}

//idk why this makes it so laggy. look into lter
void extra_controls()
{/*
    int inputs_triggered = 0;
    
    if(IsKeyDown(KEY_F) && IsKeyDown(KEY_LEFT_CONTROL));
    {
        if (!inputs_triggered)
        {       
            //ToggleBorderlessWindowed();
        }
        inputs_triggered = 1;
    }
*/
}

void controls(Player *player, int (*map)[MAP_COLS])
{
    move_player(player, map);
    //extra_controls();
}