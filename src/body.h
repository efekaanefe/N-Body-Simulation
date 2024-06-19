#pragma once
#include "raylib.h"

class Body
{
public:
    Body();
    float mass;
    Vector2 position, velocity;

    void Update();
    void Draw();

private:

};