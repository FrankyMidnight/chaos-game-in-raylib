#include <math.h>
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const int WIN_WIDTH = 1000;
const int WIN_HEIGHT = 1000;
const int FPS = 60;

Vector2 *punti_poligono = NULL;
int facce;
Vector2 centro = {.x = WIN_WIDTH / 2.0, .y = WIN_HEIGHT / 2.0};

float multiplier = .5;
bool paused = false;

char str_sides[64];
char str_multiplier[64];
Vector2 punto_intermedio = {};
Vector2 punto_ultimo = {.x = 23, .y = 520};

void setup();
void input();
void update();
void render();
void cleanup();

void calc_intermedio(Vector2);
Vector2 *genera_punti_poligono(int facce);

void clear_screen();

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        puts("Usage : chaos_game NUM (NUM = Number of faces)");
        return 0;
    }
    facce = atoi(argv[1]);
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
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(WIN_WIDTH, WIN_HEIGHT, "Chaos game  +/- on numpad adjusts multiplier and nums set base multiplier");
    punti_poligono = genera_punti_poligono(facce);
    clear_screen();
}
void cleanup()
{
    free(punti_poligono);
    CloseWindow();
}
void input()
{
    // Spazio per pausa
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
        printf("Paused : %d\n", paused);
    }
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
        // scelta casuale del punto di paragone
        int ref_vert = GetRandomValue(0, facce - 1);
        calc_intermedio(punti_poligono[ref_vert]);
    }
}
void render()
{
    BeginDrawing();
    // Display punto calcolato
    DrawPixelV(punto_ultimo, ORANGE);
    // Display poligon

    sprintf(str_sides, "Facce : %d", facce);
    DrawText(str_sides, 800, 40, 18, WHITE);
    sprintf(str_multiplier, "Moltiplicatore : %.2f", multiplier);
    DrawText(str_multiplier, 800, 60, 18, WHITE);
    DrawText("NUMPAD 1-9 set multiplier .1 - .9\n+/- Adjust multiplier +/- .01", 700, 900, 18, WHITE);
    EndDrawing();
}
void calc_intermedio(Vector2 punto_paragone)
{
    // calcolo punto intermedio secondo il moltiplicatore (default = 0.5 metà)
    punto_intermedio.x = punto_paragone.x + (punto_ultimo.x - punto_paragone.x) * multiplier;
    punto_intermedio.y = punto_paragone.y + (punto_ultimo.y - punto_paragone.y) * multiplier;
    punto_ultimo = punto_intermedio;
}
void clear_screen()
{
    BeginDrawing();
    ClearBackground(BLACK);
    for (int i = 0; i < facce; ++i)
    {

        DrawCircleV(punti_poligono[i], 3, ORANGE);
    }
    EndDrawing();
}
Vector2 *genera_punti_poligono(int facce)
{
    punti_poligono = calloc(facce, sizeof(Vector2));
    float angolo_giro = 2 * 3.14159;
    float x = 0.0;
    float y = 0.0;
    float raggio = 400.0;
    for (int i = 0; i < facce; ++i)
    {
        y = cos(angolo_giro * ((i + 1) / (float)facce)) * raggio;
        x = sin(angolo_giro * ((i + 1) / (float)facce)) * raggio;
        x += centro.x;
        y += centro.y;
        punti_poligono[i] = (Vector2){.x = x, .y = y};
        // printf("Punto %d x : %.f\ty : %.f\n", i, x, y);
    }
    return punti_poligono;
}