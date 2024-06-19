#include "simulation.h"
#include "constants.h"
#include "math.h"
#include "raymath.h"
#include <stdio.h>

Simulation::Simulation(){
    Initialize();
}

void Simulation::Initialize(){
     for (int i = 0; i < NUM_BODIES; i++) {
        bodies[i].position = {(float)GetRandomValue(100, 700), (float)GetRandomValue(100, 500)};
        bodies[i].velocity = {0, 0};
        // bodies[i].acceleration = {0, 0};
        bodies[i].mass = GetRandomValue(1, 100) * 10e10;
    }
}

void Simulation::Run(float deltaTime){
    DrawBodies();
    UpdateBodies(deltaTime);

    // Debug();
}

void Simulation::DrawBodies(){
    for (int i = 0; i < NUM_BODIES; i++) {
        DrawCircleV(bodies[i].position, 5, bodyColor);
    }
}

void Simulation::UpdateBodies(float deltaTime){
    for (int i = 0; i < NUM_BODIES; i++) {
        Vector2 totalForce = {0, 0};
        for (int j = 0; j < NUM_BODIES; j++) {
            if (i != j) {
                Vector2 force = CalculateForce(bodies[i], bodies[j]);
                totalForce = Vector2Add(totalForce, force);
            }
        }
        Vector2 acceleration = Vector2Scale(totalForce, 1.0f / bodies[i].mass);
        bodies[i].velocity = Vector2Add(bodies[i].velocity, Vector2Scale(acceleration, deltaTime));
    }

    for (int i = 0; i < NUM_BODIES; i++) {
        bodies[i].position = Vector2Add(bodies[i].position, Vector2Scale(bodies[i].velocity, deltaTime));
    }
}

Vector2 Simulation::CalculateForce(Body a, Body b) {
    Vector2 force = {0, 0};
    Vector2 difference = Vector2Subtract(b.position, a.position);
    float distance = Vector2Length(difference);
    if (distance == 0) return force; // Avoid division by zero
    float strength = (G * a.mass * b.mass) / (distance * distance);
    Vector2 direction = Vector2Normalize(difference);
    force = Vector2Scale(direction, strength);
    return force;
}

void Simulation::Debug(){
    for (int i = 0; i < NUM_BODIES; i++) {
        printf("Body %d: Position = (%.2f, %.2f)\n", i, bodies[i].position.x, bodies[i].position.y);
        printf("Body %d: Mass = (%.2f)\n", i, bodies[i].mass/5);
    }
}