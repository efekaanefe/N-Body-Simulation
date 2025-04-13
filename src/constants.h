#ifndef CONSTANTS_H
#define CONSTANTS_H
#pragma once
#include "raylib.h"

const int screenWidth = 1200;
const int screenHeight = 800;
const Color backgroundColor = BLACK;
const Color bodyColor = WHITE;
const Color quadtreeColor = GRAY;
// simulation
const int NUM_BODIES = 10000;
const float G = 6.67430e-11;
const float MIN_DISTANCE = 200.0f;
const float epsilon = 1e-2f;

// quadtree
const int QT_NODE_CAPACITY = 100;

#endif
