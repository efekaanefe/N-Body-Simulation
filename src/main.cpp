#include <raylib.h>
#include "simulation.h"

int main()
{
    InitWindow(screenWidth, screenHeight, "2D N-Body Simulation");
    SetTargetFPS(75);

    Simulation sim = Simulation(); 

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(backgroundColor);

            sim.Run();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}