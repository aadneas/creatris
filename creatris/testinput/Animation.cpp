//
// Created by Aadne on 29.10.2020.
//

#include "Animation.h"

#include <iostream>

Animation::Animation(){
    totalTime = 0.0f;
    iterator.x = 0;
    iterator.y = 0;
    reset.x = 0;
    reset.y = 0;
    counter = 0;
    xNullifier = 1;
    playerOffset = 1.7;
}

Animation::Animation(sf::Texture* texture, sf::Vector2f frameCount, float switchTime){
    this->frameCount = frameCount;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    iterator.x = 0;
    iterator.y = 0;
    reset.x = 0;
    reset.y = 0;
    counter = 0;
    xNullifier = 1;
    playerOffset = 1.7;

    uvRect.width = texture->getSize().x / float(frameCount.x);
    uvRect.height = texture->getSize().y / float(frameCount.y);
}


void Animation::Update(float deltaTime, bool facingRight, int cycleCount, sf::Vector2i cycleStart){

    //If new input parameters reset iterator counters
    if(reset.x != cycleStart.x || reset.y != cycleStart.y){
        iterator.x = 0;
        iterator.y = 0;
        counter = 0;
        xNullifier = 1;
    }
    reset.x = cycleStart.x;
    reset.y = cycleStart.y;


    totalTime += deltaTime;

    if(totalTime >= switchTime){
        totalTime -= switchTime;
        iterator.x++;
        counter++;

        //If cycled through all frames start over
        if(counter >= cycleCount){
            iterator.x = 0;
            iterator.y = 0;
            counter = 0;
            xNullifier = 1;
        }
        //If not cycled through all frames, but no more frames on the row go to next row
        else if(currentFrame.x >= frameCount.x - playerOffset){
            iterator.y++;
            iterator.x = 0;
            currentFrame.y++;
            xNullifier = 0;
        }
    }


    currentFrame.x = (cycleStart.x * xNullifier ) + iterator.x;
    currentFrame.y = cycleStart.y + iterator.y;


    //Orientation code
    uvRect.top = currentFrame.y * uvRect.height;
    if(facingRight){
        //Facing right
        uvRect.left = currentFrame.x * abs(uvRect.width);
        uvRect.width = abs(uvRect.width);
    }
    else{
        //Facing left
        //Inverting the image on the y-axis
        uvRect.left = (currentFrame.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }
}

bool Animation::fullAnimation(float deltaTime, bool facingRight, int cycleCount, sf::Vector2i cycleStart) {

    //If new input parameters reset iterator counters
    if(reset.x != cycleStart.x || reset.y != cycleStart.y){
        iterator.x = 0;
        iterator.y = 0;
        counter = 0;
        xNullifier = 1;
    }
    reset.x = cycleStart.x;
    reset.y = cycleStart.y;

    totalTime += deltaTime;

    if(totalTime >= switchTime){
        totalTime -= switchTime;
        iterator.x++;
        counter++;

        //If cycled through all frames return true
        if(counter >= cycleCount){
            return false;
        }
            //If not cycled through all frames, but no more frames on the row go to next row
        else if(currentFrame.x >= frameCount.x - playerOffset){
            iterator.y++;
            iterator.x = 0;
            currentFrame.y++;
            xNullifier = 0;
        }
    }
    currentFrame.x = (cycleStart.x * xNullifier ) + iterator.x;
    currentFrame.y = cycleStart.y + iterator.y;

    //Orientation code
    uvRect.top = currentFrame.y * uvRect.height;
    if(facingRight){
        //Facing right
        uvRect.left = currentFrame.x * abs(uvRect.width);
        uvRect.width = abs(uvRect.width);
    }
    else{
        //Facing left
        //Inverting the image on the y-axis
        uvRect.left = (currentFrame.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }

    return true;
}