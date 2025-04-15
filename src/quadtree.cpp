#include "quadtree.h"
#include "body.h"
#include "constants.h"
#include <cctype>
#include <cmath>
#include <cstdio>
#include <raylib.h>
#include <raymath.h>
#include <vector>

Quadtree::Quadtree(Rectangle boundary) {
    this->boundary = boundary;
    this->bodies.clear();
    this->capacity = QT_NODE_CAPACITY;
    this->isDivided = false;
    this->centerOfMass = {0, 0};
    this->totalMass = 0;

    this->northWest = nullptr;
    this->northEast = nullptr;
    this->southWest = nullptr;
    this->southEast = nullptr;
}

void Quadtree::Insert(Body body) {
    // Check if this body is within this quadtree node's boundary
    if (!CheckCollisionPointRec(body.position, boundary)) {
        return;
    }

    // Update center of mass calculation
    Vector2 weightedPosition = {
        centerOfMass.x * totalMass + body.position.x * body.mass,
        centerOfMass.y * totalMass + body.position.y * body.mass,
    };
    totalMass += body.mass;

    if (totalMass > 0) {
        centerOfMass.x = weightedPosition.x / totalMass;
        centerOfMass.y = weightedPosition.y / totalMass;
    }

    // If we have space and aren't divided, just add the body
    if (bodies.size() < QT_NODE_CAPACITY && !isDivided) {
        bodies.push_back(body);
        return;
    }

    if (!isDivided) {
        Subdivide();
    }

    northWest->Insert(body);
    northEast->Insert(body);
    southWest->Insert(body);
    southEast->Insert(body);
}

void Quadtree::Subdivide() {
    float x = this->boundary.x;
    float y = this->boundary.y;
    float w = this->boundary.width;
    float h = this->boundary.height;

    // Use half width and height
    float halfW = w / 2.0f;
    float halfH = h / 2.0f;

    // boundaries for northwest, northeast, southwest, southeast
    Rectangle nw = {x, y, halfW, halfH};
    Rectangle ne = {x + halfW, y, halfW, halfH};
    Rectangle sw = {x, y + halfH, halfW, halfH};
    Rectangle se = {x + halfW, y + halfH, halfW, halfH};

    this->northWest = new Quadtree(nw);
    this->northEast = new Quadtree(ne);
    this->southWest = new Quadtree(sw);
    this->southEast = new Quadtree(se);

    this->isDivided = true;

    // Insert the bodies to children
    for (const Body &b : this->bodies) {
        this->northWest->Insert(b);
        this->northEast->Insert(b);
        this->southWest->Insert(b);
        this->southEast->Insert(b);
    }

    this->bodies.clear();
}

Vector2 Quadtree::CalculateForce(Body body, float theta) {
    if (totalMass == 0) {
        return {0, 0};
    }

    Vector2 force = {0, 0};
    float dx = centerOfMass.x - body.position.x;
    float dy = centerOfMass.y - body.position.y;
    float distance = sqrt(dx * dx + dy * dy);

    float s = sqrt(boundary.width * boundary.height);
    float ratio = s / distance;

    if (!isDivided || ratio < theta) {
        if (distance > MIN_DISTANCE) {
            float forceMagnitude = G * body.mass * totalMass /
                                   (distance * distance);
            Vector2 direction = Vector2Normalize({dx, dy});
            force.x = direction.x * forceMagnitude;
            force.y = direction.y * forceMagnitude;
        }
    } else {
        // recurse into children...
        if (isDivided) {
            Vector2 nwForce = northWest->CalculateForce(body, theta);
            Vector2 neForce = northEast->CalculateForce(body, theta);
            Vector2 swForce = southWest->CalculateForce(body, theta);
            Vector2 seForce = southEast->CalculateForce(body, theta);
            force.x = nwForce.x + neForce.x + swForce.x + seForce.x;
            force.y = nwForce.y + neForce.y + swForce.y + seForce.y;
        }
    }
    return force;
}

void Quadtree::Clear() {
    bodies.clear();
    totalMass = 0;
    centerOfMass = {0, 0};

    if (isDivided) {
        delete northWest;
        delete northEast;
        delete southWest;
        delete southEast;

        northWest = nullptr;
        northEast = nullptr;
        southWest = nullptr;
        southEast = nullptr;

        isDivided = false;
    }
}

void Quadtree::Draw() {
    DrawRectangleLinesEx(boundary, 1, quadtreeColor);

    if (isDivided) {
        northWest->Draw();
        northEast->Draw();
        southWest->Draw();
        southEast->Draw();
    }
}
