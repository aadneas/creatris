#ifndef PROJECT_COLLISIONS_H
#define PROJECT_COLLISIONS_H

#include <iostream>
#include <Box2d/include/box2d/box2d.h>
#include <SFML/Graphics.hpp>

class Collisions {
public:
    void CreateStatic(b2World& World, float X, float Y);
    b2Body* CreateDynamic(b2World& World, int X, int Y);

};

#endif //PROJECT_COLLISIONS_H
