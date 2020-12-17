//
// Created by Aadne on 16.12.2020.
//

#include "NecroBall.h"


NecroBall::NecroBall(b2World* world, b2Vec2 position, bool necroLeft, float angle) {
    //Appearance
    ballTexture.loadFromFile("textures/necroball.png");
    size.x = 70;
    size.y = 20;
    ball.setSize(size);
    ball.setOrigin(size.x/2 - 15, size.y/2);
    ball.setTexture(&ballTexture);

    //Animation.Update parameters
    cycleStart.x = 0;
    cycleStart.y = 0;
    cycleCount = 3;

    //Texture framecount
    frameCount.x = 3;
    frameCount.y = 1;

    //Time per frame in animation
    switchTime = 0.1f;

    //Direction (copied just so we can use it in Fly function)
    facingLeft = necroLeft;

    //Passing information from necroBall class to animation class
    animation.frameCount = frameCount;
    animation.switchTime = switchTime;
    animation.uvRect.width = ballTexture.getSize().x / float(frameCount.x);
    animation.uvRect.height = ballTexture.getSize().y / float(frameCount.y);

    //Physics
    ptr = &data;

    //Make it spawn from the necromancers staff
    if(facingLeft){
        position.x -= 80.f;
        position.y -= 50.f;
    }
    else{
        position.x += 80.f;
        position.y -= 50.f;
    }
    ballCol = createPhysical::createBall(world, position, ptr, BALL, ENVIRONMENT | PLAYER | BOUNDARY);
    ball.setPosition(30 * ballCol->GetPosition().x, 30 * ballCol->GetPosition().y);

    ballAngle = angle;
    flipped = false;
}

NecroBall::~NecroBall() {
    ptr = NULL;
}

void NecroBall::Fly(float deltaTime) {
    b2Vec2 velocity = ballCol->GetLinearVelocity();

    float forceX = 0.2f * cos(ballAngle);
    float forceY = 0.2f * sin(ballAngle);

    if(flipped){
        forceX = -forceX;
        forceY = -forceY;
        ball.setFillColor(sf::Color::Red);
    }

    //Apply force and limit velocity
    if(facingLeft){
        if(velocity.x > -2){
            ballCol->ApplyLinearImpulseToCenter(b2Vec2(forceX, forceY), true);
        }
    }
    else{
        if(velocity.x < 2){
            ballCol->ApplyLinearImpulseToCenter(b2Vec2(forceX, forceY), true);
        }
    }

    animation.Update(deltaTime, facingLeft, cycleCount, cycleStart);


    if(facingLeft){
        ball.setPosition(30 * ballCol->GetPosition().x, 30 * ballCol->GetPosition().y);
        ball.setRotation(ballAngle * (180/M_PI) + 180);
    }

    else{
        ball.setPosition((30 * ballCol->GetPosition().x) - 30, 30 * ballCol->GetPosition().y);
        ball.setRotation(ballAngle * (180/M_PI));
    }


    ball.setTextureRect(animation.uvRect);
}