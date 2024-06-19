#pragma once
#include "raylib.h"

class Body
{
public:
    Body();
    void Update();
    void Draw();

    float mass;
    Vector2 position, velocity;

private:

};