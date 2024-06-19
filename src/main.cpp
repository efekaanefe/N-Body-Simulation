#include <raylib.h>
#include "simulation.h"

int main()
{
    InitWindow(screenWidth, screenHeight, "2D N-Body Simulation");
    // SetTargetFPS(75);

    Simulation sim = Simulation(); 

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();
        
        BeginDrawing();
        ClearBackground(backgroundColor);

            sim.Run(deltaTime);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}