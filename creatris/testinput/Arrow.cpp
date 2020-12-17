//
// Created by Aadne on 13.12.2020.
//

#include "Arrow.h"
#include <iostream>


Arrow::Arrow(b2World* world, b2Vec2 position) {
    //Appearance
    arrowTexture.loadFromFile("textures/arrow.png");
    size.x = 66;
    size.y = 6;
    arrow.setSize(size);
    arrow.setOrigin(size.x/2, size.y/2);
    arrow.setTexture(&arrowTexture);


    //Physics
    ptr = &data;
    arrowCol = createPhysical::createArrow(world, position, ptr, ARROW, ENVIRONMENT | ENEMY | BOUNDARY);
}

Arrow::~Arrow() {
    ptr = NULL;
}

void Arrow::Fly(bool facingRight, int force) {
    if(facingRight)
        arrowCol->ApplyLinearImpulseToCenter(b2Vec2(force, 0), true);
    else{
        arrowCol->ApplyLinearImpulseToCenter(b2Vec2(-force, 0), true);
        arrow.setRotation(180);
    }

}