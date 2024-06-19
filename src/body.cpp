#include "body.h"


Body::Body()
{
    
}

void Body::Update()
{
 }

void Body::Draw()
{
    DrawCircle(position.x, position.y, mass, WHITE);
}