//
// Created by Aadne on 16.12.2020.
//

#ifndef TESTINPUT_NECROBALL_H
#define TESTINPUT_NECROBALL_H

#include <SFML/Graphics.hpp>
#include "Box2d/include/box2d/box2d.h"
#include "createPhysical.h"
#include "Animation.h"
#include <math.h>


class NecroBall {
public:
    NecroBall(b2World* world, b2Vec2 position, bool necroLeft, float angle);

    void Fly(float deltaTime);

    ~NecroBall();

    //Appearance
    sf::RectangleShape ball;
    sf::Texture ballTexture;
    sf::Vector2f size;
    Animation animation;
    bool facingLeft;
    sf::Vector2f frameCount;
    float switchTime;
    sf::Vector2i cycleStart;
    int cycleCount;

    //Travel angle
    float ballAngle;
    bool flipped;

    //Physical
    b2Body* ballCol;
    int data = 15;
    int* ptr;

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
};


#endif //TESTINPUT_NECROBALL_H
