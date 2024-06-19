#pragma once
#include <vector>
#include "body.h"
#include "constants.h"

class Simulation{
    public:
        Simulation();
        void Run();

    private:
        Body bodies[NUM_BODIES];

        void Initialize();
        void DrawBodies();
        void Simulate(float deltaTime);
        void Debug();
};