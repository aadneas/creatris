//
// Created by Aadne on 11.12.2020.
//

#include "Box2d/include/box2d/box2d.h"
#include "GlobalVariables.h"

#ifndef TESTINPUT_PHYSICS_H
#define TESTINPUT_PHYSICS_H


class Physics {
public:
    Physics();

    //Velocity
    b2Vec2 velocity;

    //These are mask and category bits for filtering out collision
    enum categories{
        ENVIRONMENT = 0x0001,
        PLAYER      = 0x0002,
        ENEMY       = 0x0004,
        PSENSOR     = 0x0008,
        ESENSOR     = 0x0010,
        ARROW       = 0x0020,
        FEET        = 0x0040,
        BALL        = 0x0080,
        BOUNDARY    = 0x0100,
    };

    b2PolygonShape Shape;

    //Collision - Floor
    b2BodyDef BodyDef2;
    b2Body* Floor;

    b2PolygonShape Shape2;
    b2FixtureDef FixtureDef2;

    //Collision - Floor2
    b2BodyDef BodyDef4;
    b2Body* Floor2;

    b2PolygonShape Shape4;
    b2FixtureDef FixtureDef4;

    //Wall
    b2BodyDef BodyDef3;
    b2Body* wall;
    b2FixtureUserData UserData;
    int Data = 80;
    int* Ptr;

    b2PolygonShape Shape3;
    b2FixtureDef FixtureDef3;

    //Top of wall for friction
    b2FixtureDef FixtureDef6;

    //Boundary
    b2Body* boundary;
    b2BodyDef boundaryBD;
    b2FixtureDef boundaryFD;
    b2FixtureUserData boundaryUserData;
    int boundaryData = 30;
    int* boundaryPtr;

};


#endif //TESTINPUT_PHYSICS_H
