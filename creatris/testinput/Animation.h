//
// Created by Aadne on 29.10.2020.
//

#ifndef TESTINPUT_ANIMATION_H
#define TESTINPUT_ANIMATION_H

#include <SFML\Graphics.hpp>


class Animation {
public:
    Animation();

    Animation(sf::Texture* texture, sf::Vector2f frameCount, float switchTime);
//    ~Animation();

    //The composite
    sf::IntRect uvRect;

    //Needs starting time passed(deltaTime), which direction is faced(facingRight),
    //number of frames to animate(cycleCount), and where to begin iterating through the frames(cycleStart)
    void Update(float deltaTime, bool facingRight, int cycleCount, sf::Vector2i cycleStart);

    //Function to play an animation in its entirety such as pull/sheath sword or jump
    bool fullAnimation(float deltaTime, bool facingRight, int cycleCount, sf::Vector2i cycleStart);

    //Frame selecting variables
    sf::Vector2f frameCount;
    sf::Vector2u currentFrame;
    sf::Vector2u iterator;
    sf::Vector2u reset;
    int counter;
    int xNullifier;

    //Keeping track of frame switching time
    float totalTime;
    float switchTime;

    //For playerOffset see player.cpp
    float playerOffset;
};


#endif //TESTINPUT_ANIMATION_H
