#pragma once
#include <vector>
#include "body.h"
#include "constants.h"

class Simulation{
    public:
        Simulation();
        void Run(float deltaTime);

    private:
        Body bodies[NUM_BODIES];

        void Initialize();
        void DrawBodies();
        void UpdateBodies(float deltaTime);
        Vector2 CalculateForce(Body a, Body b);
        void Debug();
};