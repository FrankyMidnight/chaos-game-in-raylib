#include <math.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const int WIN_WIDTH = 1000;
const int WIN_HEIGHT = 1000;
Color text_color = {.r = 110, .g = 120, .b = 100, .a = 255};
Vector2 *poligon_vertex = NULL;
int faces;
Vector2 window_center = {.x = WIN_WIDTH / 2.0, .y = WIN_HEIGHT / 2.0};

float multiplier = .5;
bool paused = false;

char str_sides[64];
char str_multiplier[64];
Vector2 intermediate_point = {};
Vector2 last_intermediate = {.x = 23, .y = 520};

void setup();
void input();
void update();
void render();
void cleanup();

void calc_intermediate(Vector2);
Vector2 *generate_poligon_vertices(int faces);

void clear_screen();

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        puts("Usage : chaos_game NUM (NUM = Number of faces)");
        return 0;
    }
    // set faces from argument 1
    faces = atoi(argv[1]);
    setup();
    while (!WindowShouldClose())
    {
        input();
        update();
        render();
    }
    cleanup();
    return 0;
}

void setup()
{
    // set anti aliasing
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "Chaos game  +/- on numpad adjusts multiplier and nums set base multiplier");
    // generate poligon vertices
    poligon_vertex = generate_poligon_vertices(faces);
    clear_screen();
}
void cleanup()
{
    free(poligon_vertex);
    CloseWindow();
}
void input()
{
    // PAUSE on SPACE
    if (IsKeyPressed(KEY_SPACE))
    {
        if (paused == true)
        {
            paused = false;
        }
        else
        {
            paused = true;
        }
    }
    // SET MULTIPLIER
    else if (IsKeyPressed(KEY_KP_1))
    {
        multiplier = .1;
        clear_screen();
    }
    else if (IsKeyPressed(KEY_KP_2))
    {
        multiplier = .2;
        clear_screen();
    }
    else if (IsKeyPressed(KEY_KP_3))
    {
        multiplier = .3;
        clear_screen();
    }
    else if (IsKeyPressed(KEY_KP_4))
    {
        multiplier = .4;
        clear_screen();
    }
    else if (IsKeyPressed(KEY_KP_5))
    {
        multiplier = .5;
        clear_screen();
    }
    else if (IsKeyPressed(KEY_KP_6))
    {
        multiplier = .6;
        clear_screen();
    }
    else if (IsKeyPressed(KEY_KP_7))
    {
        multiplier = .7;
        clear_screen();
    }
    else if (IsKeyPressed(KEY_KP_8))
    {
        multiplier = .8;
        clear_screen();
    }
    else if (IsKeyPressed(KEY_KP_9))
    {
        multiplier = .9;
        clear_screen();
    }
    // ADJUST MULTIPLIER
    else if (IsKeyPressed(KEY_KP_ADD))
    {
        multiplier += .01;
        clear_screen();
    }
    else if (IsKeyPressed(KEY_KP_SUBTRACT))
    {
        multiplier -= .01;
        clear_screen();
    }
}
void update()
{
    if (!paused)
    {
        // RANDOM POLIGON VERTEX
        int ref_vert = GetRandomValue(0, faces - 1);
        // FIND INTERMEDIATE
        calc_intermediate(poligon_vertex[ref_vert]);
    }
}
void render()
{
    BeginDrawing();
    // Display calculated pixel
    DrawPixelV(last_intermediate, ORANGE);

    // Display TEXT
    sprintf(str_sides, "Faces : %d", faces);
    DrawText(str_sides, 800, 40, 18, text_color);
    sprintf(str_multiplier, "Multiplier : %.2f", multiplier);
    DrawText(str_multiplier, 800, 60, 18, text_color);
    DrawText("NUMPAD 1-9 set multiplier .1 - .9\n+/- Adjust multiplier +/- .01", 700, 900, 18, text_color);
    EndDrawing();
}
void calc_intermediate(Vector2 sample_vertex)
{
    // Calculate intermediate point at multiplier distance between random vertex and last calculated
    intermediate_point.x = sample_vertex.x + (last_intermediate.x - sample_vertex.x) * multiplier;
    intermediate_point.y = sample_vertex.y + (last_intermediate.y - sample_vertex.y) * multiplier;
    // save in last intermediate
    last_intermediate = intermediate_point;
}
void clear_screen()
{
    BeginDrawing();
    ClearBackground(BLACK);
    // draw a little circle at every poligon vertex
    for (int i = 0; i < faces; ++i)
    {
        DrawCircleV(poligon_vertex[i], 3, ORANGE);
    }
    EndDrawing();
}
Vector2 *generate_poligon_vertices(int faces)
{
    poligon_vertex = calloc(faces, sizeof(Vector2));
    float two_radians = 2 * 3.14159;
    float x = 0.0;
    float y = 0.0;
    float radius = 400.0;
    // find poligon vertices coordinates
    for (int i = 0; i < faces; ++i)
    {
        // Slice 2PI on sin and cos and multiply by the radius
        y = cos(two_radians * ((i) / (float)faces)) * radius;
        x = sin(two_radians * ((i) / (float)faces)) * radius;
        // add poligon center offset
        x += window_center.x;
        y += window_center.y;
        // save coordinate
        poligon_vertex[i] = (Vector2){.x = x, .y = y};
    }
    return poligon_vertex;
}