//
// Created by Aadne on 01.12.2020.
//
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Animation.h"
#include "GeneralSound.h"
#include "Physics.h"
#include "GlobalVariables.h"

#include "ContactListener.h"
#include "Menu.h"

#include "Arrow.h"

#ifndef INPUT_INPUT_H
#define INPUT_INPUT_H


class Input {
public:
    Input();
    int menu_input(sf::RenderWindow& window);
    void shoot_arrow(b2Vec2 position, bool facingRight, int force);
    void hit_enemies(bool facingRight);
    void player_input2(sf::RenderWindow& window, float deltaTime);

    Player* player = new Player();
    Physics physics;


    ContactListener contact;

    //Main menu
    Menu menu;


private:
    //Sound
    GeneralSound sound;

    //For polling
    sf::Event event;

    //Animation
    Animation animation;
    sf::Vector2i cycleStart;
    int cycleCount;
    int swordSwingCycle;
    bool inProcess;
    bool fullAnimation;
    float debounceTime;


    //Movement
    b2Vec2 currentSpeed;
    float impulse;
    bool blockMovement;
    float speedDivider;


    //Keys
    bool a, d, w, s, r, q, space, f, enter;
    //Check release (These are single input per press keys)
    bool w2, s2, r2, space2, enter2;
};


#endif //INPUT_INPUT_H
