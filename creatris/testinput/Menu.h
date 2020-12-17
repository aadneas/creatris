//
// Created by Aadne on 13.12.2020.
//

#ifndef TESTINPUT_MENU_H
#define TESTINPUT_MENU_H

#include "SFML/Graphics.hpp"
#include "GeneralSound.h"
#include "GlobalVariables.h"
#include <fstream>
#include <string>
#include <iostream>

class Menu {
public:
    Menu();

    void Up();
    void Down();

    void Main();
    void Options();
    void PlayerDead();
    void Volume(sf::RenderWindow &window);

    int selected;
    int stage;
    std::vector<sf::Text> menu;
    GeneralSound sound;
private:
    sf::Font menuFont;
    sf::Font titleFont;
    sf::Font infoFont;

    int character;
};


#endif //TESTINPUT_MENU_H
