#include "quadtree.h"
#include "body.h"
#include "constants.h"
#include <cctype>
#include <raylib.h>
#include <vector>

Quadtree::Quadtree(Rectangle boundary) : boundary(boundary) {
  this->boundary = boundary;
  this->bodies.clear();
  this->isDivided = false;
  this->northWest = nullptr;
  this->northEast = nullptr;
  this->southWest = nullptr;
  this->southEast = nullptr;
}

void Quadtree::Insert(Body body) {
  // Check if this body is within this quadtree node's boundary
  if (!CheckCollisionPointRec(body.position, this->boundary)) {
    return;
  }
  // If we have space and aren't divided, just add the body
  if (this->bodies.size() < QT_NODE_CAPACITY && !isDivided) {
    this->bodies.push_back(body);
    return;
  }

  if (!isDivided) {
    this->Subdivide();
  }

  northWest->Insert(body);
  northEast->Insert(body);
  southWest->Insert(body);
  southEast->Insert(body);
}

void Quadtree::Subdivide() {
  int x = this->boundary.x;
  int y = this->boundary.y;
  int w = this->boundary.width;
  int h = this->boundary.height;

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

  for (const Body &b : this->bodies) {
    this->northWest->Insert(b);
    this->northEast->Insert(b);
    this->southWest->Insert(b);
    this->southEast->Insert(b);
  }

  this->bodies.clear();
}

// Find all points that appear within a boundary
std::vector<Body> Quadtree::QueryRange(Rectangle range) {
  std::vector<Body> found;
  // If range doesn't intersect boundary, return empty vector
  if (!CheckCollisionRecs(range, boundary)) {
    return found;
  }
  // Add all bodies in this quad that are within the range
  for (const Body &b : bodies) {
    if (CheckCollisionPointRec(b.position, range)) {
      found.push_back(b);
    }
  }

  // If this quad is divided, check children too
  if (isDivided) {
    std::vector<Body> foundNW = northWest->QueryRange(range);
    std::vector<Body> foundNE = northEast->QueryRange(range);
    std::vector<Body> foundSW = southWest->QueryRange(range);
    std::vector<Body> foundSE = southEast->QueryRange(range);

    // Combine results from children
    found.insert(found.end(), foundNW.begin(), foundNW.end());
    found.insert(found.end(), foundNE.begin(), foundNE.end());
    found.insert(found.end(), foundSW.begin(), foundSW.end());
    found.insert(found.end(), foundSE.begin(), foundSE.end());
  }
  return found;
}
