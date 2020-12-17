//
// Created by Aadne on 13.12.2020.
//

#ifndef TESTINPUT_ARROW_H
#define TESTINPUT_ARROW_H

#include <SFML/Graphics.hpp>
#include "Box2d/include/box2d/box2d.h"
#include "createPhysical.h"

class Arrow {
public:
    Arrow(b2World* world, b2Vec2 position);

    void Fly(bool facingRight, int force);

    ~Arrow();

    //Appearance
    sf::RectangleShape arrow;
    sf::Texture arrowTexture;
    sf::Vector2f size;

    //Physical
    b2Body* arrowCol;
    int data = 20;
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


#endif //TESTINPUT_ARROW_H
