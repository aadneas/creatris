//
// Created by Aadne on 11.12.2020.
//

#include "Physics.h"
#include "math.h"


Physics::Physics(){
    //Velocity of player
    velocity.x = 0;
    velocity.y = 0;

    //Collision - Floor
    BodyDef2.position = b2Vec2(650.0f/ 30, 1000.0f/ 30);
    BodyDef2.type = b2_staticBody;
    Floor = world.CreateBody(&BodyDef2);

    Shape2.SetAsBox((1300.0f/ 30.f)/2, (20.0f/ 30.f)/2.f);
    FixtureDef2.density = 0.0f;
    FixtureDef2.filter.categoryBits = ENVIRONMENT;
    FixtureDef2.filter.maskBits = PLAYER | ENEMY | FEET | ARROW | BALL;
    FixtureDef2.shape = &Shape2;
    FixtureDef2.friction = 0.9f;
    Floor->CreateFixture(&FixtureDef2);

    //Floor2
    BodyDef4.position = b2Vec2(1720.0f/ 30, 1000.0f/ 30);
    BodyDef4.type = b2_staticBody;
    Floor2 = world.CreateBody(&BodyDef4);

    Shape4.SetAsBox((400.0f/ 30.f)/2, (20.0f/ 30.f)/2.f);
    FixtureDef4.density = 0.0f;
    FixtureDef4.filter.categoryBits = ENVIRONMENT;
    FixtureDef4.filter.maskBits = PLAYER | ENEMY | FEET | ARROW | BALL;
    FixtureDef4.shape = &Shape4;
    Floor2->CreateFixture(&FixtureDef4);

    //Wall
    BodyDef3.position = b2Vec2(970.0f/ 30, 810.0f/ 30);
    BodyDef3.type = b2_staticBody;
    wall = world.CreateBody(&BodyDef3);

    Shape3.SetAsBox((20.0f/ 30)/2, (540.0f/ 30)/2);
    FixtureDef3.density = 0.0f;
    FixtureDef3.friction = 0.0f;
    FixtureDef3.filter.categoryBits = ENVIRONMENT;
    FixtureDef3.filter.maskBits = PLAYER | ENEMY | FEET | ARROW | BALL | ESENSOR;
    Ptr = &Data;
    UserData.pointer = (uintptr_t)Ptr;
    FixtureDef3.userData = UserData;
    FixtureDef3.shape = &Shape3;
    wall->CreateFixture(&FixtureDef3);

    //Top of wall
    Shape.SetAsBox((19.5f/30)/2, 6.f/30, b2Vec2(0,-8.85f), 0);
    FixtureDef6.filter.categoryBits = ENVIRONMENT;
    FixtureDef6.filter.maskBits = PLAYER | ENEMY | FEET | ARROW | BALL;
    FixtureDef6.shape = &Shape;
    wall->CreateFixture(&FixtureDef6);

    //Boundary
//    boundaryBD.position = b2Vec2((1920.f/30)/2, (1080.f/30)/2);
//    //boundaryBD.position = b2Vec2(0, 0);
//    boundaryBD.type = b2_staticBody;
//    boundary = world.CreateBody(&boundaryBD);
//    //Shape.SetAsBox(1920.f/60, 6.f/60, b2Vec2(0,1080.f/60), 0);
//    boundaryFD.filter.categoryBits = BOUNDARY;
//    boundaryFD.filter.maskBits = PLAYER | ENEMY | ARROW | BALL;
//    boundaryPtr = &boundaryData;
//    boundaryUserData.pointer = (uintptr_t)boundaryPtr;
//    boundaryFD.userData = boundaryUserData;
//    boundaryFD.shape = &Shape;
//    Shape.SetAsBox( 1920.f/60, 1, b2Vec2(0, -1920.f/30), 0);//ground
//    boundary->CreateFixture(&boundaryFD);
//    Shape.SetAsBox( 1920.f/60, 1, b2Vec2(0, 1920.f/30), 0);//ceiling
//    boundary->CreateFixture(&boundaryFD);
//    Shape.SetAsBox( 1, 1080.f/60, b2Vec2(-1080.f/30, 1080.f/30), 0);//left wall
//    boundary->CreateFixture(&boundaryFD);
//    Shape.SetAsBox( 1, 1080.f/60, b2Vec2(1080.f/30, 1080.f/30), 0);//right wall
//    boundary->CreateFixture(&boundaryFD);

}