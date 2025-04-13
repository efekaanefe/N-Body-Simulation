#pragma once
#include "body.h"
#include "constants.h"
#include <math.h>
#include <raylib.h>
#include <vector>

class Quadtree {
  public:
    Quadtree(Rectangle boundary);

    // methods
    void Insert(Body body);
    void Subdivide();
    Vector2 CalculateForce(Body body, float theta);
    void Clear();
    void Draw();

    // Destructor
    ~Quadtree() {
        // Clean up child nodes
        if (isDivided) {
            delete northWest;
            delete northEast;
            delete southWest;
            delete southEast;
        }
    }

  private:
    int capacity;
    Rectangle boundary;
    std::vector<Body> bodies;
    bool isDivided;

    Vector2 centerOfMass;
    float totalMass;

    // children
    Quadtree *northWest;
    Quadtree *northEast;
    Quadtree *southWest;
    Quadtree *southEast;
};
