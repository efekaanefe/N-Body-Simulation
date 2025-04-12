#include "body.h"

Rectangle Body::GetAABB() const {
    // Assuming the body is a point-like object or small enough to be treated as a point,
    // and you want to give it a standard bounding box size (say 5x5)
    float size = 5.0f;
    return {
        position.x - size / 2,
        position.y - size / 2,
        size,
        size
    };
}
