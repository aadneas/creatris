//
// Created by Aadne on 06.12.2020.
//

#include "Enemy1.h"
#include <iostream>

Enemy1::Enemy1(b2World* world, b2Vec2 position){
    enemyTexture.loadFromFile("textures/necro.png");
    size.x = 270;
    size.y = 270;
    shape.setSize(size);
    shape.setTexture(&enemyTexture);
    shape.setOrigin(225.f, 185.f);

    //Animation.Update parameters
    cycleStart.x = 0;
    cycleStart.y = 0;
    cycleCount = 4;

    //Texture framecount
    frameCount.x = 6;
    frameCount.y = 7;

    //Time per frame in animation
    switchTime = 0.1f;

    //Timer for certain behaviors
    timer = 0;

    inProcess = false;

    //Enemy properties
    speed = 200;
    health = 3;
    facingLeft = false;
    walk = true;
    jump = false;
    playerClose = false;
    spottedPlayer = false;
    combat = false;


    //Passing information from enemy class to animation class
    animation.frameCount = frameCount;
    animation.switchTime = switchTime;
    animation.uvRect.width = enemyTexture.getSize().x / float(frameCount.x);
    animation.uvRect.height = enemyTexture.getSize().y / float(frameCount.y);

    //Physics
    sizeB2.x = 37.f;
    sizeB2.y = 83.f;
    int* dataPtr = &data;
    body = createPhysical::createBody(world, sizeB2, position, dataPtr, ENEMY, ENVIRONMENT | PSENSOR | ARROW | BOUNDARY);

    //Sensor cone
    eyesFD.isSensor = true;
    eyesFD.filter.categoryBits = ESENSOR;
    eyesFD.filter.maskBits = PLAYER | ENVIRONMENT;
    eyes = createPhysical::createSensorCone(40, 100);
    eyesFD.density = 0.f;
    eyesFD.shape = &eyes;
    sensorPtr = &Sensor;
    sensorUserData.pointer = (uintptr_t)sensorPtr;
    eyesFD.userData = sensorUserData;
    body->CreateFixture(&eyesFD);
}

Enemy1::~Enemy1() {
    sensorPtr = NULL;
}

void Enemy1::Behavior(float deltaTime) {
    velocity = body->GetLinearVelocity();

    timer += deltaTime;


    if(!blockMovement){
        if(timer >= 2) {
            facingLeft = !facingLeft;
            body->SetLinearVelocity(b2Vec2(0, 0));
            timer = 0;
        }
        if(facingLeft){
            body->SetTransform(body->GetPosition(), (M_PI/180));
            if(velocity.x > -2){
                body->ApplyLinearImpulseToCenter(b2Vec2(-10.f, 0), true);
            }
        }
        else{
            body->SetTransform(body->GetPosition(), 180*(M_PI/180));
            if(velocity.x < 2){
                body->ApplyLinearImpulseToCenter(b2Vec2(10.f, 0), true);
            }
        }
    }



    //Check if player is within sight
    if(playerClose)
        spottedPlayer = rayCasting();
    else
        spottedPlayer = false;

    //Shoot in two second intervals
    if(spottedPlayer){
        cycleStart.x = 4;
        cycleStart.y = 1;
        cycleCount = 5;
        if(timer > 0.4f){
            shoot_ball(body->GetPosition(), facingLeft, deltaTime);
            timer = -0.2f;
        }
        blockMovement = true;
    }
    else{
        blockMovement = false;
    }

    //Idle
    if(!velocity.x && !velocity.y && !spottedPlayer){
        cycleStart.x = 0;
        cycleStart.y = 0;
        cycleCount = 4;
    }

    if(velocity.x && !spottedPlayer){
        cycleStart.x = 4;
        cycleStart.y = 0;
        cycleCount = 6;
    }


    if(facingLeft)
        shape.setPosition(30 * body->GetPosition().x, 30 * body->GetPosition().y);
    else
        shape.setPosition((30 * body->GetPosition().x) + 180.f, 30 * body->GetPosition().y);


    animation.Update(deltaTime, facingLeft, cycleCount, cycleStart);
    shape.setTextureRect(animation.uvRect);

}

//Shoot a ball
void Enemy1::shoot_ball(b2Vec2 position, bool facingLeft, float deltaTime) {
    position.x = position.x * 30;
    position.y = position.y * 30;
    auto * ball = new NecroBall(&world, position, facingLeft, attackAngle);
    ballVector.push_back(ball);
    ballBodyObject.emplace(ball->ballCol, ball);
}

bool Enemy1::rayCasting() {
    b2RayCastInput input;
    b2Vec2 position = body->GetPosition();
    b2Fixture* closestFixture;
    float angle;

    //Offset to cast from staff since this is where ball will spawn from, this is also around eye level
    if(facingLeft){
        position.x -= 80.f/30;
        position.y -= 50.f/30;
    }
    else{
        position.x += 80.f/30;
        position.y -= 50.f/30;
    }

    //Start cast from
    input.p1 = position;
    //Check if player is in vision cone of this enemy cause else it's pointless to ray cast
    auto player = playerBodyObject.begin()->first;
    if(std::find(bodiesSeen.begin(), bodiesSeen.end(), player) != bodiesSeen.end()){
        b2Vec2 playerPosition = player->GetPosition();
        input.p2 = playerPosition;
        b2Vec2 delta;
        delta.x = playerPosition.x - position.x;
        delta.y = playerPosition.y - position.y;
        angle = atan2(delta.y, delta.x);
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
                    attackAngle = angle;
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

void Enemy1::Hurt() {
    health--;
    if(health <= 0){
        bodiesToDestroy.push_back(body);
    }
}

