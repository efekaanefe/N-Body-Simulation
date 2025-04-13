#pragma once
#include "raylib.h"

class Body {
  public:
    float mass;
    Vector2 position, velocity, acceleration;

    // Overload the equality operator (==)
    bool operator==(const Body &other) const {
        // Define what makes two bodies "the same"
        // In this example, we'll consider them the same if all their member
        // variables (mass, position, velocity, acceleration) are equal.
        return (mass == other.mass && position.x == other.position.x &&
                position.y == other.position.y &&
                velocity.x == other.velocity.x &&
                velocity.y == other.velocity.y &&
                acceleration.x == other.acceleration.x &&
                acceleration.y == other.acceleration.y);
    }

    // Overload the inequality operator (!=) by negating the equality operator
    bool operator!=(const Body &other) const { return !(*this == other); }
};
