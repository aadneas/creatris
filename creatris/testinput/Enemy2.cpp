//
// Created by Aadne on 15.12.2020.
//

#include "Enemy2.h"

Enemy2::Enemy2(b2World *world, b2Vec2 position) {
    enemyTexture.loadFromFile("textures/bat.png");
    size.x = 100;
    size.y = 100;
    shape.setSize(size);
    shape.setTexture(&enemyTexture);
    shape.setOrigin(55.f, 50.f);

    //Animation.Update parameters
    cycleStart.x = 0;
    cycleStart.y = 2;
    cycleCount = 8;

    //Texture framecount
    frameCount.x = 10;
    frameCount.y = 3;

    //Time per frame in animation
    switchTime = 0.1f;

    //Timer for certain behaviors
    timer = 0;

    //Enemy properties
    speed = 200;
    facingRight = false;
    combat = false;
    health = 1;

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
    sizeB2.x = 37.f;
    sizeB2.y = 20.f;
    int* dataPtr = &data;
    body = createPhysical::createBody(world, sizeB2, position, dataPtr, ENEMY, ENVIRONMENT | PSENSOR | ARROW | BOUNDARY);
    body->SetGravityScale(0);

    //Sensor cone
    eyesFD.isSensor = true;
    eyesFD.filter.categoryBits = ESENSOR;
    eyesFD.filter.maskBits = PLAYER;
    eyes = createPhysical::createSensorCone(25, 360);
    eyesFD.density = 0.f;
    eyesFD.shape = &eyes;
    sensorPtr = &Sensor;
    sensorUserData.pointer = (uintptr_t)sensorPtr;
    eyesFD.userData = sensorUserData;
    body->CreateFixture(&eyesFD);
}

void Enemy2::Behavior(float deltaTime) {
    velocity = body->GetLinearVelocity();

    timer += deltaTime;

    if(timer >= 4) {
        facingRight = !facingRight;
        body->SetLinearVelocity(b2Vec2(0, 0));
        timer = 0;
    }

    if(facingRight){
        if(velocity.x < 2){
            body->ApplyLinearImpulseToCenter(b2Vec2(0.1f, 0), true);
        }
    }
    else{
        if(velocity.x > -2){
            body->ApplyLinearImpulseToCenter(b2Vec2(-0.1f, 0), true);
        }
    }


    animation.Update(deltaTime, facingRight, cycleCount, cycleStart);
    shape.setPosition(30 * body->GetPosition().x, 30 * body->GetPosition().y);

    if(facingRight)
        shape.setPosition(30 * body->GetPosition().x + 8, 30 * body->GetPosition().y);
    else
        shape.setPosition((30 * body->GetPosition().x), 30 * body->GetPosition().y);

    shape.setTextureRect(animation.uvRect);
}

bool Enemy2::rayCasting() {
    b2RayCastInput input;
    b2Vec2 position = body->GetPosition();
    b2Fixture* closestFixture;

    //Start cast from
    input.p1 = position;
    //Check if player is in vision cone of this enemy cause else it's pointless to ray cast
    auto player = playerBodyObject.begin()->first;
    if(std::find(bodiesSeen.begin(), bodiesSeen.end(), player) != bodiesSeen.end()){
        b2Vec2 playerPosition = player->GetPosition();
        input.p2 = playerPosition;
        input.maxFraction = 1;
        float closestPoint = 1;


        for(auto i : bodiesSeen){
            b2Fixture* fixture = i->GetFixtureList()->GetNext();
            while(fixture->IsSensor()){
                fixture = fixture->GetNext();
            }
            b2RayCastOutput output;
            if (!fixture->RayCast(&output, input, 0)){
                continue;
            }
            if(output.fraction < closestPoint){
                closestPoint = output.fraction;
                closestFixture = fixture;
            }
        }
        b2Fixture* closestBody = closestFixture;
        if(closestBody != 0){
            if(closestBody->GetUserData().pointer != 0){
                if(*(int*)closestBody->GetUserData().pointer == 2){
                    //Player is closest
                    return true;
                }
                else{
                    return false;
                }
            }
        }

    }
    return false;
}

void Enemy2::Hurt() {
    health--;
    if(health <= 0){
        bodiesToDestroy.push_back(body);
    }
}