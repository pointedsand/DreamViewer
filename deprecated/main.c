#include <stdio.h>
#include <stdlib.h>

#include <math.h>

#include <raylib.h>


//preprocessor directives
#define MAP_ROWS 20
#define MAP_COLS 20
#define CELL_SIZE 50

#define NUM_RAYS 100
#define VIEW_HEIGHT 50
#define FONT_SIZE 25

//objects
typedef struct {
    float x;
    float y;
    float angle;

} Player;


//function definitions//

//debug/development
void print_map(int (*map)[MAP_COLS]);
void init_map(int (*map)[MAP_COLS]);
void draw_map(int (*map)[MAP_COLS]);
void draw_player(Player player);
void draw_raycasts(Player player, float ray_distances[NUM_RAYS]);
//player
void move_player(Player *player);
//raycast
float cast_ray(int (*map)[MAP_COLS], Player player, float angle);
int raycast(int (*map)[MAP_COLS], Player player, float ray_distances[NUM_RAYS]);
void printArr(float arr[NUM_RAYS]);
//rendering
void draw_walls(Player player, float ray_distances[NUM_RAYS]);
char get_wall_character(float distance);
void render_view(Player player, float ray_distances[NUM_RAYS]);

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
        move_player(&player);
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

//functions

//debug/development
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
void printArr(float arr[NUM_RAYS]) 
{
    for(int i = 0; i < NUM_RAYS; i++) 
    {
        printf("arr[%d] = %f\n", i, arr[i]);
    }
}

//raycast
float cast_ray(int (*map)[MAP_COLS], Player player, float angle)
{
    if(!map)
    {
        return NAN;
    }

    //ray direction
    float x_dir = cosf(angle);
    float y_dir = sinf(angle);

    //map cell where ray originates
    int map_x = (int)player.x; //boundaries on negative side of the cell
    int map_y = (int)player.y;

    int step_x;
    int step_y;

    if(x_dir < 0) {step_x = -1;} else {step_x = 1;}
    if(y_dir < 0) {step_y = -1;} else {step_y = 1;}

    int next_x = map_x;
    int next_y = map_y;

    if(step_x == 1) {next_x += 1;} //map_x + 1 = boundary on positive side of the cell
    if(step_y == 1) {next_y += 1;}

    float delta_x = next_x - player.x;
    float delta_y = next_y - player.y;

    
    //calculate distances to next boundary and calculate boundary increments on step
    float dist_to_x_boundary;
    float x_boundary_increment;
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
            map_y += step_y;
            hit_distance = dist_to_y_boundary;
            dist_to_y_boundary += y_boundary_increment;
        }
        else
        {
            map_x += step_x;
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

//controls
void move_player(Player *player) 
{
    float move_speed = 2.0;
    float turn_speed = 2.0;

    float delta_t = GetFrameTime();

    if(IsKeyDown(KEY_W))
    {
        player->x += cosf(player->angle) * move_speed * delta_t;
        player->y += sinf(player->angle) * move_speed * delta_t;
    }

        if(IsKeyDown(KEY_S))
    {
        player->x -= cosf(player->angle) * move_speed * delta_t;
        player->y -= sinf(player->angle) * move_speed * delta_t;
    }

    if(IsKeyDown(KEY_A))
    {
        player->angle -= turn_speed * delta_t;
    }

    if(IsKeyDown(KEY_D))
    {
        player->angle += turn_speed * delta_t;
    }
}

//rendering
/*void draw_walls(Player player, float ray_distances[NUM_RAYS])
{
    float char_width = (float)GetScreenWidth() / NUM_RAYS;
    float char_height = (float)GetScreenHeight() / VIEW_HEIGHT;

    float ray_angle = player.angle - PI/6;
    float angle_increment = (PI/3) / (NUM_RAYS-1);

    for (int i = 0; i < NUM_RAYS; i++) 
    {
        float corrected_distance = ray_distances[i] * cosf(ray_angle - player.angle); //fixes fish eye distortion

        float wall_height = 30.0f / corrected_distance;
        int wall_top = (VIEW_HEIGHT/2) - wall_height/2;
        int wall_bottom = (VIEW_HEIGHT/2) + wall_height/2;

        char character;
        if (corrected_distance < 1.5) { character = '@'; }
        else if (corrected_distance < 2.5) { character = '#'; }
        else if (corrected_distance < 3.5) { character = '*'; }
        else if (corrected_distance < 4.5) { character = '+'; }
        else if (corrected_distance < 5.5) {character = '-'; }
        else if (corrected_distance < 6.5) {character = ':'; }
        else { character = '.'; } 

        char symbol[2] = {character, '\0'};

        for (int j = wall_top; j < wall_bottom; j++) 
        {
            float x = i * char_width;
            float y = j * char_height;
            DrawText(
            symbol, x, y,
            FONT_SIZE, BLUE
            );
        }
    }
}
*/

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