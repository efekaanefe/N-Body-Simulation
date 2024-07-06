#include "quadtree.h"
#include "raylib.h"
#include "body.h"
#include <vector>

Quadtree::Quadtree(Rectangle boundary): boundary(boundary){
    
}

Quadtree::Insert(Body body){
    if (bodies.size() < capacity){
        this->bodies.push_back(body);
    } else{
        if (!isDivided){
            Subdivide();
            isDivided = true;
        }
    }
}

Quadtree::Subdivide(){
    int x = this->boundary.x;
    int y = this->boundary.y;
    int w = this->boundary.w;
    int h = this->boundary.h;

    // boundaries for northwest, northeast, southwest, southeast
    Rectangle nw = { x-w/2, y-h/2, w/2, h/2};
    Rectangle ne = { x+w/2, y-h/2, w/2, h/2};
    Rectangle sw = { x-w/2, y+h/2, w/2, h/2};
    Rectangle se = { x+w/2, y+h/2, w/2, h/2};

    this->northWest = Quadtree(nw);
    this->northEast = Quadtree(ne);
    this->southWest = Quadtree(sw);
    this->southEast = Quadtree(se);

}
