#include "raylib.h"


int main(int argc, char const *argv[])
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Strange Attractors");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Simulator Boilerplate is working!", 190, 200, 20, GREEN);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
