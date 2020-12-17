//
// Created by Aadne on 01.12.2020.
//

#include "Player.h"

Player::Player() {
    //Player model
    playerTexture.loadFromFile("textures/advent3.png");
    size.x = 200;
    size.y = 200;
    shape.setSize(size);
    shape.setTexture(&playerTexture);

    //Texture framecount
    //Framecount.x is 7.7 because advent3.png image is 385x740 but each frame
    //is 50x37. 50 * 7.7 = 385
    frameCount.x = 7.7;
    frameCount.y = 20;

    //Time per frame in animation
    switchTime = 0.1f;

    //Health hearts texture
    heartTexture.loadFromFile("textures/heart.png");
    emptyheartTexture.loadFromFile("textures/heart2.png");
    heartSize.x = heartSize.y = 128;
    heartPosition.x = 50;
    heartPosition.y = 50;
    for(int i = 0; i < 5; i++){
        heart[i].setSize(heartSize);
        heart[i].setTexture(&heartTexture);
        heart[i].setPosition(heartPosition);
        heartPosition.x += 64;
    }

    //Physics
    sizeB2.x = 37.f;
    sizeB2.y = 83.f;
    b2Vec2 position (200, 500);
    int* dataPtr = &playerData;
    playerCol = createPhysical::createBody(&world, sizeB2, position, dataPtr, PLAYER, ENVIRONMENT | ESENSOR | BALL | BOUNDARY);

    //Sensor for feet so we know when player is grounded
    Shape.SetAsBox(33.f/30, 6.f/30, b2Vec2(0,2.7f), 0);
    feetFD.density = 0.f;
    feetFD.filter.categoryBits = FEET;
    feetFD.filter.maskBits = ENVIRONMENT;
    feetFD.isSensor = true;

    //Setting data for collision sensor in feet so as to recognize that it is the feet
    feetPtr = &feetData;
    feetUserData.pointer = (uintptr_t)feetPtr;
    feetFD.userData = feetUserData;
    feetFD.shape = &Shape;
    playerCol->CreateFixture(&feetFD);

    //TESTING EYES
    float radius = 3.5;
    b2Vec2 vertices[8];
    vertices[0].Set(0,0);
    for (int i = 0; i < 7; i++) {
        float angle = i / 6.0 * 130 * (M_PI/180) - 65 * (M_PI/180);
        vertices[i+1].Set( radius * cosf(angle), radius * sinf(angle) );
    }
    sensor.Set(vertices, 8);
    sensorFD.density = 0.f;
    sensorFD.filter.categoryBits = PSENSOR;
    sensorFD.filter.maskBits = ENEMY;
    sensorFD.isSensor = true;
    sensorPtr = &rightSensor;
    sensorUserData.pointer = (uintptr_t)sensorPtr;
    sensorFD.userData = sensorUserData;
    sensorFD.shape = &sensor;
    playerCol->CreateFixture(&sensorFD);
    //Other way
    for (int i = 0; i < 7; i++) {
        float angle = i / 6.0 * 130 * (M_PI/180) - 245 * (M_PI/180);
        vertices[i+1].Set( radius * cosf(angle), radius * sinf(angle) );
    }
    sensor.Set(vertices, 8);
    sensorPtr = &leftSensor;
    sensorUserData.pointer = (uintptr_t)sensorPtr;
    sensorFD.userData = sensorUserData;
    sensorFD.shape = &sensor;
    playerCol->CreateFixture(&sensorFD);


    //Player properties
    speed = 100;
    arrowForce = 15;
    facingRight = true;
    sword = false;
    health = 5;
}

void Player::changeHealth(int change) {
    if(change < 0){
        for(int i = health; i > (health + change); i--){
            heart[i-1].setTexture(&emptyheartTexture);
        }
    }
    else{
        for(int i = health; i < (health + change); i++){
            heart[i-1].setTexture(&heartTexture);
        }
    }

    if(health + change < 0){
        //Die
        return;
    }
    else if(health + change > 5){
        return;
    }
    else{
        health = health + change;
    }
}