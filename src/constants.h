#ifndef CONSTANTS_H
#define CONSTANTS_H
#pragma once
#include "raylib.h"

const int screenWidth = 800;
const int screenHeight = 600;
const Color backgroundColor = BLACK;
const Color bodyColor = WHITE;
const Color quadtreeColor = GRAY;
// simulation
const int NUM_BODIES = 200;
const float G = 6.67430e-11;
const float MIN_DISTANCE = 0.01;

// quadtree
const int QT_NODE_CAPACITY = 4;
const int SEARCH_AREA_SIZE = 100;

#endif
