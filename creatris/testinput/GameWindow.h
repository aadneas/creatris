//
// Created by Aadne on 01.12.2020.
//
#include <SFML/Graphics.hpp>
#include "map/map.h"
#include "Box2d/include/box2d/box2d.h"
#include "Input.h"
#include "SFMLDebugDraw.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include <iostream>
#include "GlobalVariables.h"

#ifndef WINDOW_WINDOW_H
#define WINDOW_WINDOW_H


class GameWindow {
public:
    GameWindow();
    void RunningGame();


private:
    sf::RenderWindow window;
    float deltaTime;
    float timer;
    sf::Clock clock;

    //Menu state
    int mainMenu;

};


#endif //WINDOW_WINDOW_H
