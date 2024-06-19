#include "body.h"
#include <raylib.h>

Body::Body()
{
    
}

void Body::Update()
{
 }

void Body::Draw()
{
    DrawCircle(pos.x, pos.y, mass, WHITE);
}