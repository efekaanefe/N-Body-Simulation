#include "simulation.h"
#include "constants.h"
#include <random>
#include "math.h"

Simulation::Simulation(){
    Initialize();
}

void Simulation::Initialize(){
     for (int i = 0; i < NUM_BODIES; i++) {
        bodies[i].position = {(float)GetRandomValue(100, 700), (float)GetRandomValue(100, 500)};
        bodies[i].velocity = {0, 0};
        bodies[i].mass = GetRandomValue(1, 100);
    }
}

void Simulation::Run(){
    DrawBodies();

    Debug();
}

void Simulation::DrawBodies(){
    for (int i = 0; i < NUM_BODIES; i++) {
        DrawCircleV(bodies[i].position, 5, bodyColor);
    }
}

void Simulation::Simulate(float deltaTime){

}

void Simulation::Debug(){
    for (int i = 0; i < NUM_BODIES; i++) {
        printf("Body %d: Position = (%.2f, %.2f)\n", i, bodies[i].position.x, bodies[i].position.y);
        printf("Body %d: Mass = (%.2f)\n", i, bodies[i].mass);
    }
}