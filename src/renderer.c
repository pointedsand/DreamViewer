#include <math.h>
#include <raylib.h>
#include "renderer.h"

char get_wall_character(float distance)
{
    char character;
    if (distance < 1.5) { character = '@'; }
    else if (distance < 2.5) { character = '#'; }
    else if (distance < 3.5) { character = '*'; }
    else if (distance < 4.5) { character = '+'; }
    else if (distance < 5.5) {character = '-'; }
    else if (distance < 6.5) {character = ':'; }
    else { character = '.'; }     
    return character;
}

void draw_floor() 
{
    float char_width = (float)GetScreenWidth() / NUM_RAYS;
    float char_height = (float)GetScreenHeight() / VIEW_HEIGHT;

    int horizon = VIEW_HEIGHT / 2;

    for(int i = horizon; i < VIEW_HEIGHT; i++)
    { 
        for(int j = 0; j < NUM_RAYS; j++) 
        {
            float x = j * char_width;
            float y = i * char_height;

            DrawText(
                ".", x, y,
                FONT_SIZE, BEIGE
            );
        }
    }
}

void render_view(Player player, float ray_distances[NUM_RAYS])
{
    float char_width = (float)GetScreenWidth() / NUM_RAYS;
    float char_height = (float)GetScreenHeight() / VIEW_HEIGHT;

    float ray_angle = player.angle - PI/6;
    float angle_increment = (PI/3) / (NUM_RAYS-1);

    for(int i = 0; i < NUM_RAYS; i++)
    {
        float corrected_distance = ray_distances[i] * cosf(ray_angle - player.angle); //fixes fish eye distortion
        float wall_height = 30.0f / corrected_distance;
        int wall_top = (VIEW_HEIGHT/2) - wall_height/2;
        int wall_bottom = (VIEW_HEIGHT/2) + wall_height/2;

        for(int j = 0; j < VIEW_HEIGHT; j++) 
        {
            float x = i * char_width;
            float y = j * char_height;
            if (j < wall_top) //sky
            {

            }
            else if (j < wall_bottom) //wall
            {

                char character = get_wall_character(corrected_distance);
                char symbol[2] = {character, '\0'};
                DrawText(
                symbol, x, y,
                FONT_SIZE, DARKBLUE
            );  
            }
            else //floor
            {
                /*
                DrawText(
                    ".", x, y,
                    FONT_SIZE, DARKBROWN
                ); */
            }
        }
        ray_angle += angle_increment;
    }
}