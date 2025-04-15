#include "simulation.h"
#include "body.h"
#include "constants.h"
#include "math.h"
#include "quadtree.h"
#include "raylib.h"
/*#include "raymath.h"*/
#include <stdio.h>

Simulation::Simulation()
    : quadtree({0, 0, (float)screenWidth, (float)screenHeight}) {
    for (int i = 0; i < NUM_BODIES; i++) {
        bodies[i].position = {
            (float)GetRandomValue(0.2 * screenWidth, 0.8 * screenWidth),
            (float)GetRandomValue(0.2 * screenHeight, 0.8 * screenHeight)};
        // bodies[i].position = {(float)GetRandomValue(300, 500),
        // (float)GetRandomValue(200, 400)};
        bodies[i].velocity = {0, 0};
        bodies[i].acceleration = {0, 0};
        // bodies[i].mass = GetRandomValue(1, 100) * 10e10;
        bodies[i].mass = 1e12;
    }
}

void Simulation::Run(float deltaTime) {
    UpdateBodies(deltaTime);
    quadtree.Draw();
    DrawBodies();
    /*Debug();*/
}

void Simulation::DrawBodies() {
    for (int i = 0; i < NUM_BODIES; i++) {
        DrawCircleV(bodies[i].position, 0.9, bodyColor);
    }
}

void Simulation::UpdateBodies(float deltaTime) {

    quadtree.Clear();

    for (Body &body : bodies) {
        quadtree.Insert(body);
    }

    // Calculate forces on each body using Barnes-Hut approximation
    for (Body &body : bodies) {
        Vector2 force = quadtree.CalculateForce(
            body, 1.0f); // theta = 0.5 is common, (0.1 accurate, 1.0 fast)

        // Apply force to calculate acceleration
        Vector2 acceleration = {force.x / body.mass, force.y / body.mass};

        /*printf("Vector2: x = %f, y = %f\n", acceleration.x, acceleration.y);*/

        // Update velocity (integrate acceleration)
        body.velocity.x += acceleration.x * deltaTime;
        body.velocity.y += acceleration.y * deltaTime;
    }
    // Update positions
    for (Body &body : bodies) {
        body.position.x += body.velocity.x * deltaTime;
        body.position.y += body.velocity.y * deltaTime;
    }
}

void Simulation::Debug() {

    for (int i = 0; i < NUM_BODIES; i++) {
        printf("Body %d: Position = (%.2f, %.2f)\n", i, bodies[i].position.x,
               bodies[i].position.y);
        // printf("Body %d: Mass = (%.2f)\n", i, bodies[i].mass/5);
    }
}
