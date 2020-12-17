//
// Created by Aadne on 06.12.2020.
//
#include <SFML/Graphics.hpp>
#include "Box2d/include/box2d/box2d.h"
#include "Animation.h"
#include "GeneralSound.h"
#include "createPhysical.h"
#include "GlobalVariables.h"
#include "NecroBall.h"
#include <vector>
#include <math.h>

#include <iostream>



#ifndef TESTINPUT_ENEMY1_H
#define TESTINPUT_ENEMY1_H


class Enemy1 {
public:
    Enemy1(b2World* world, b2Vec2 position);
    void Behavior(float deltaTime);
    void shoot_ball(b2Vec2 position, bool facingLeft, float deltaTime);
    bool rayCasting();
    void Hurt();

    ~Enemy1();

    GeneralSound sound;

    //Texture and animation
    Animation animation;
    sf::RectangleShape shape;
    sf::Texture enemyTexture;
    sf::Vector2f size;
    sf::Vector2f frameCount;
    float switchTime;
    float timer;
    sf::Vector2f movement;
    sf::Vector2i cycleStart;
    int cycleCount;
    bool inProcess;
    bool fullAnimation;

    //Physics
    b2Body* body;
    b2Vec2 sizeB2;
    b2Vec2 velocity;
    int data = 6;
    //These are mask and category bits for filtering out collision
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
    //Vision cone for enemy
    b2PolygonShape eyes;
    b2FixtureDef eyesFD;
    b2FixtureUserData sensorUserData;
    int Sensor = 7;
    int* sensorPtr;

    //What bodies are in sight
    std::vector<b2Body*> bodiesSeen;

    //Movement
    float speed;
    bool facingLeft;
    float attackAngle;
    int health;
    bool dead;
    bool walk;
    sf::Vector2f position;
    bool jump;
    bool playerClose;
    bool spottedPlayer;
    bool combat;
    bool blockMovement;
};


#endif //TESTINPUT_ENEMY1_H
