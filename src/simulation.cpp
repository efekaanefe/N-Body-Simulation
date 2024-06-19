#include "simulation.h"
#include "constants.h"
#include <random>
#include "math.h"

Simulation::Simulation(){

}

void Simulation::Initialize(){
     for (int i = 0; i < NUM_BODIES; i++) {
        bodies[i].position = {float(GetRandomValue(100, 700)), float(GetRandomValue(100, 500))};
        bodies[i].velocity = {0, 0};
        bodies[i].mass = GetRandomValue(1, 100) * 1e10;
    }
}

void Simulation::Run(){
    DrawBodies();
}

void Simulation::DrawBodies(){
    for (int i = 0; i < NUM_BODIES; i++) {
        DrawCircleV(bodies[i].position, 5, bodyColor);
    }
}