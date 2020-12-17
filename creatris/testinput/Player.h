//
// Created by Aadne on 01.12.2020.
//
#include <SFML/Graphics.hpp>
#include "Box2d/include/box2d/box2d.h"
#include "GlobalVariables.h"
#include "createPhysical.h"
#include "math.h"

#ifndef PLAYER_PLAYER_H
#define PLAYER_PLAYER_H


class Player {
public:
    Player();
    void changeHealth(int change);

    //Texture and animation
    sf::RectangleShape shape;
    sf::Texture playerTexture;
    sf::Vector2f size;
    sf::Vector2f frameCount;
    float switchTime;

    //Health HUD
    std::array<sf::RectangleShape, 5> heart;
    sf::Texture heartTexture;
    sf::Texture emptyheartTexture;
    sf::Vector2f heartSize;
    sf::Vector2f heartPosition;

    //Physics
    b2Body* playerCol;
    b2Vec2 sizeB2;
    b2FixtureUserData playerUserData;
    int playerData = 2;
    int* dataPtr;

    //Feet for player
    b2FixtureDef feetFD;
    b2PolygonShape Shape;
    b2FixtureUserData feetUserData;
    int feetData = 3;
    int* feetPtr;

    //TESTING SIGHT
    b2PolygonShape sensor;
    b2FixtureDef sensorFD;
    b2FixtureUserData sensorUserData;
    int rightSensor = 4;
    int leftSensor = 5;
    int* sensorPtr;

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


    //Movement
    float speed;
    float arrowForce;
    bool facingRight;
    bool sword;
    int health;
};


#endif //PLAYER_PLAYER_H
