#pragma once
#include "body.h"
#include "constants.h"
#include <raylib.h>
#include <vector>

class Quadtree {
public:
  Quadtree(Rectangle boundary);

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
  const int capacity = QT_NODE_CAPACITY;
  Rectangle boundary;
  std::vector<Body> bodies;
  bool isDivided = false;

  // children
  Quadtree *northWest;
  Quadtree *northEast;
  Quadtree *southWest;
  Quadtree *southEast;

  // methods
  void Insert(Body body);
  void Subdivide();
  std::vector<Body> QueryRange(Rectangle range);
};
