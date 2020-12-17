//
// Created by Aadne on 15.12.2020.
//

#ifndef TESTINPUT_ENEMY2_H
#define TESTINPUT_ENEMY2_H

#include <SFML/Graphics.hpp>
#include "Box2d/include/box2d/box2d.h"
#include "Animation.h"
#include "GeneralSound.h"
#include "createPhysical.h"
#include "GlobalVariables.h"

class Enemy2 {
public:
    Enemy2(b2World* world, b2Vec2 position);
    void Hurt();
    void Behavior(float deltaTime);
    bool rayCasting();



    GeneralSound sound;

    //Texture and animation
    Animation animation;
    sf::RectangleShape shape;
private:
    sf::Texture enemyTexture;
    sf::Vector2f size;
    sf::Vector2f frameCount;
    float switchTime;
    sf::Vector2f movement;
    sf::Vector2i cycleStart;
    int cycleCount;
    bool inProcess;
    bool fullAnimation;

    //Physics
    b2Body* body;
    b2Vec2 sizeB2;
    b2Vec2 velocity;
    b2Vec2 position;
    int data = 8;

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
    int Sensor = 9;
    int* sensorPtr;

    //What bodies are in sight
    std::vector<b2Body*> bodiesSeen;


    //Movement
    float speed;
    int health;
    bool facingRight;
    bool combat;
    float timer;



};


#endif //TESTINPUT_ENEMY2_H
