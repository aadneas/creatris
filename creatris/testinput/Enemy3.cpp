//
// Created by Aadne on 15.12.2020.
//

#include "Enemy3.h"

Enemy3::Enemy3(b2World *world, b2Vec2 position) {
    enemyTexture.loadFromFile("textures/wolf.png");
    size.x = 300;
    size.y = 300;
    shape.setSize(size);
    shape.setTexture(&enemyTexture);
    shape.setOrigin(150.f, 150.f);

    //Animation.Update parameters
    cycleStart.x = 0;
    cycleStart.y = 2;
    cycleCount = 12;

    //Texture framecount
    frameCount.x = 18;
    frameCount.y = 4;

    //Time per frame in animation
    switchTime = 0.1f;

    //Timer for certain behaviors
    timer = 0;

    //Enemy properties
    speed = 200;
    facingRight = false;
    combat = false;

    //Shape.move parameters
    movement.x = 0;
    movement.y = 0;


    //Passing information from enemy class to animation class
    animation.frameCount = frameCount;
    animation.switchTime = switchTime;
    animation.uvRect.width = enemyTexture.getSize().x / float(frameCount.x);
    animation.uvRect.height = enemyTexture.getSize().y / float(frameCount.y);
    GeneralSound sound;

    //Physics
    sizeB2.x = 75.f;
    sizeB2.y = 50.f;
    int *dataPtr = &data;
    body = createPhysical::createBody(world, sizeB2, position, dataPtr, ENEMY, ENVIRONMENT | PSENSOR | ARROW | BOUNDARY);
    body->SetGravityScale(1);

    //Sensor cone
    eyesFD.isSensor = true;
    eyesFD.filter.categoryBits = ESENSOR;
    eyesFD.filter.maskBits = PLAYER;
    eyes = createPhysical::createSensorCone(25, 80);
    eyesFD.density = 0.f;
    eyesFD.shape = &eyes;
    sensorPtr = &Sensor;
    sensorUserData.pointer = (uintptr_t) sensorPtr;
    eyesFD.userData = sensorUserData;
    body->CreateFixture(&eyesFD);
}

void Enemy3::Behavior(float deltaTime) {
    velocity = body->GetLinearVelocity();

    timer += deltaTime;

    if(timer >= 4) {
        facingRight = !facingRight;
        //body->SetLinearVelocity(b2Vec2(0, 0));
        timer = 0;
    }

    if(facingRight){
        body->SetTransform(body->GetPosition(), 180*(M_PI/180));
        if(velocity.x < 2){
            //body->ApplyLinearImpulseToCenter(b2Vec2(0.1f, 0), true);
        }
    }
    else{
        body->SetTransform(body->GetPosition(), (M_PI/180));
        if(velocity.x > -2){
            //body->ApplyLinearImpulseToCenter(b2Vec2(-0.1f, 0), true);
        }
    }


    animation.Update(deltaTime, facingRight, cycleCount, cycleStart);
    shape.setPosition(30 * body->GetPosition().x, 30 * body->GetPosition().y);

    if(facingRight)
        shape.setPosition(30 * body->GetPosition().x, 30 * body->GetPosition().y);
    else
        shape.setPosition((30 * body->GetPosition().x), 30 * body->GetPosition().y);

    shape.setTextureRect(animation.uvRect);
}