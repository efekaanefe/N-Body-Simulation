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
        // bodies[i].position = {(float)GetRandomValue(100, 700), (float)GetRandomValue(100, 500)};
        bodies[i].position = {(float)GetRandomValue(300, 500), (float)GetRandomValue(200, 400)};
        bodies[i].velocity = {0, 0};
        bodies[i].acceleration = {0, 0};
        // bodies[i].mass = GetRandomValue(1, 100) * 10e10;
        bodies[i].mass = 1 * 10e10;
    }
}

void Simulation::Run(float deltaTime){
    DrawBodies();
    UpdateBodies(deltaTime);

    // Debug();
}

void Simulation::DrawBodies(){
    for (int i = 0; i < NUM_BODIES; i++) {
        DrawCircleV(bodies[i].position, 1, bodyColor);
    }
}

void Simulation::UpdateBodies(float deltaTime){

    // ---------    OPTIMIZATION     ---------
    for (int i = 0; i < NUM_BODIES; i++) {
        float m1 = bodies[i].mass;
        for (int j = i+1; j < NUM_BODIES; j++) {
            Vector2 force = CalculateForce(bodies[i], bodies[j]);

            bodies[i].acceleration = Vector2Add(bodies[i].acceleration, Vector2Scale(force, 1.0f/m1));
            bodies[j].acceleration = Vector2Add(bodies[j].acceleration, Vector2Scale(force, -1.0f/bodies[j].mass));
        }
    }

    for (int i = 0; i < NUM_BODIES; i++) {
        bodies[i].velocity = Vector2Add(bodies[i].velocity, Vector2Scale(bodies[i].acceleration, deltaTime));
        bodies[i].acceleration = {0,0};
    }

    for (int i = 0; i < NUM_BODIES; i++) {
        bodies[i].position = Vector2Add(bodies[i].position, Vector2Scale(bodies[i].velocity, deltaTime));
    }
}

Vector2 Simulation::CalculateForce(Body a, Body b) {
    Vector2 force = {0, 0};
    Vector2 difference = Vector2Subtract(b.position, a.position);
    float distance = Vector2Length(difference);
    if (distance <= MIN_DISTANCE) { 
        distance = MIN_DISTANCE;
    }
    if (distance == 0) return force; // Avoid division by zero
    float strength = (G * a.mass * b.mass) / (distance * distance);
    force = Vector2Scale(difference, strength);
    return force;
}

void Simulation::Debug(){
    for (int i = 0; i < NUM_BODIES; i++) {
        printf("Body %d: Position = (%.2f, %.2f)\n", i, bodies[i].position.x, bodies[i].position.y);
        // printf("Body %d: Mass = (%.2f)\n", i, bodies[i].mass/5);
    }
}