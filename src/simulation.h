#pragma once
#include "body.h"
#include "constants.h"
#include "quadtree.h"
#include <vector>

class Simulation {
public:
  Simulation();
  void Run(float deltaTime);
  Quadtree quadtree;

private:
  Body bodies[NUM_BODIES];

  void DrawBodies();
  void UpdateBodies(float deltaTime);
  Vector2 CalculateForce(Body a, Body b);
  void Debug();

};
