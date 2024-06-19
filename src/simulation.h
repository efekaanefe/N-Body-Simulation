#pragma once
#include <vector>
#include "body.h"
#include "constants.h"

class Simulation{
    public:
        Simulation();
        Body bodies[NUM_BODIES];

    private:
        void Initialize();
        void Run();
        void DrawBodies();
};