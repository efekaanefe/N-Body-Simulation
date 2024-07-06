#pragma once
#include "raylib.h"
#include "body.h"
#include <vector>
#include "constants.h"


class Quadtree
{
    public:
        Quadtree(Rectangle boundary);

    private:
        const int capacity = QT_NODE_CAPACITY;
        Rectangle boundary;
        std::vector<Body> bodies;
        bool isDivided = false;

        // children
        Quadtree* northWest;
        Quadtree* northEast;
        Quadtree* southWest;
        Quadtree* southEast;

        void Insert(Body body);
        void Subdivide();

};

