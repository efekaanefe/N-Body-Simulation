#pragma once
#include "raylib.h"

class Body
{
public:
    float mass;
    Vector2 position, velocity, acceleration;
    Rectangle GetAABB() const;
};
