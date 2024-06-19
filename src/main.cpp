#include <raylib.h>
#include "simulation.h"

int main()
{
    InitWindow(screenWidth, screenHeight, "2D N-Body Simulation");
    SetTargetFPS(75);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(backgroundColor);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}