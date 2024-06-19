#pragma once
#include <vector>
#include "body.h"
#include "constants.h"

class Simulation{
    public:
        Simulation();
        Body bodies[NUM_BODIES];
        void Run();

    private:
        void Initialize();
        void DrawBodies();
        void Simulate(float deltaTime);
};