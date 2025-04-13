#include "simulation.h"
#include <raylib.h>

int main() {
    InitWindow(screenWidth, screenHeight, "2D N-Body Simulation");
    // SetTargetFPS(75);

    Simulation sim = Simulation();

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        BeginDrawing();
        ClearBackground(backgroundColor);

        sim.Run(deltaTime);
        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
