//
// Created by Aadne on 14.12.2020.
//

#ifndef TESTINPUT_CREATEPHYSICAL_H
#define TESTINPUT_CREATEPHYSICAL_H

#include "Box2d/include/box2d/box2d.h"
#include <math.h>

//Creating physical bodies and sensor fixtures
//Needs THE world being used, size of the fixture, position of body, fixture user data, and bits for filtering collision.
//Category is what type of object is being created (player, enemy or environment) and mask
//is what it should collide with
class createPhysical {
public:
    static b2Body* createBody(b2World* world, b2Vec2 size, b2Vec2 position, int* Ptr, uint16 category, uint16 mask){
        b2BodyDef enemyBD;
        b2Body* enemyCol;
        b2PolygonShape enemyShape;
        b2FixtureDef enemyFD;
        b2FixtureUserData enemyUserData;

        enemyBD.position = b2Vec2(position.x / 30, position.y/ 30);
        enemyBD.type = b2_dynamicBody;
        enemyCol = world->CreateBody(&enemyBD);

        enemyShape.SetAsBox(size.x/ 30, size.y/ 30);
        enemyFD.density = 1.0f;
        enemyFD.friction = 1.0f;
        enemyFD.filter.categoryBits = category;
        enemyFD.filter.maskBits = mask;
        enemyUserData.pointer = (uintptr_t)Ptr;
        enemyFD.userData = enemyUserData;
        enemyFD.shape = &enemyShape;
        enemyCol->CreateFixture(&enemyFD);
        enemyCol->SetFixedRotation(true);

        return enemyCol;
    }

    static b2PolygonShape createSensorCone(float radius, float angle){
        b2PolygonShape eyes;
        b2Vec2 vertices[8];
        vertices[0].Set(0,0);
        for (int i = 0; i < 7; i++) {
            float value = i / 6.0 * (angle) * (M_PI/180) - ((angle/2)+ 180) * (M_PI/180);
            vertices[i+1].Set( radius * cosf(value), radius * sinf(value) );
        }
        eyes.Set(vertices, 8);
        return eyes;
    }

    static b2Body* createArrow(b2World* world, b2Vec2 position, int* Ptr, uint16 category, uint16 mask){
        b2BodyDef arrowBD;
        b2Body* arrowCol;
        b2PolygonShape arrowShape;
        b2FixtureDef arrowFD;
        b2FixtureUserData arrowUserData;

        arrowBD.position = b2Vec2(position.x / 30, position.y/ 30);
        arrowBD.type = b2_dynamicBody;
        arrowCol = world->CreateBody(&arrowBD);

        arrowShape.SetAsBox(33.f/ 30, 3.f/ 30);
        arrowFD.density = 0.5f;
        arrowFD.friction = 1.0f;
        arrowFD.filter.categoryBits = category;
        arrowFD.filter.maskBits = mask;
        arrowUserData.pointer = (uintptr_t)Ptr;
        arrowFD.userData = arrowUserData;
        arrowFD.shape = &arrowShape;
        arrowCol->CreateFixture(&arrowFD);
        arrowCol->SetFixedRotation(false);
        arrowCol->SetBullet(true);

        return arrowCol;
    }

    static b2Body* createBall(b2World* world, b2Vec2 position, int* Ptr, uint16 category, uint16 mask){
        b2BodyDef ballBD;
        b2Body* ballCol;
        b2CircleShape ballShape;
        b2FixtureDef ballFD;
        b2FixtureUserData ballUserData;

        ballBD.position = b2Vec2(position.x / 30, position.y/ 30);
        ballBD.type = b2_dynamicBody;
        ballCol = world->CreateBody(&ballBD);
        ballCol->SetGravityScale(0);

        ballShape.m_radius = 9.0f / 30;
        ballFD.density = 1.0f;
        ballFD.friction = 1.0f;
        ballFD.filter.categoryBits = category;
        ballFD.filter.maskBits = mask;
        ballUserData.pointer = (uintptr_t)Ptr;
        ballFD.userData = ballUserData;
        ballFD.shape = &ballShape;
        //ballFD.isSensor = true;
        ballCol->CreateFixture(&ballFD);
        ballCol->SetFixedRotation(false);
        ballCol->SetBullet(true);

        return ballCol;
    }
};


#endif //TESTINPUT_CREATEPHYSICAL_H
