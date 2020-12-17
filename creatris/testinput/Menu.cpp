//
// Created by Aadne on 13.12.2020.
//

#include "Menu.h"


Menu::Menu() {
    menu.resize(4);

    //Title
    titleFont.loadFromFile("font/IMMORTAL.ttf");
    menu[3].setFont(titleFont);
    menu[3].setString("Creatris");
    menu[3].setFillColor(sf::Color((rand() % 255), (rand() % 255), (rand() % 255)));
    menu[3].setPosition(550, 100);
    menu[3].setCharacterSize(200);

    //Info
    infoFont.loadFromFile("font/Chronosfer.otf");

    //Menu options
    menuFont.loadFromFile("font/alba.ttf");
    for(int i; i <= 2; i++){
        menu[i].setFont(menuFont);
        menu[i].setCharacterSize(100);
        menu[i].setPosition(800, 400 +(i*100));
    }

    menu[0].setString("Play");
    menu[1].setString("Options");
    menu[2].setString("Quit");

    menu[0].setFillColor(sf::Color::Red);
    menu[1].setFillColor(sf::Color::White);
    menu[2].setFillColor(sf::Color::White);


    selected = 0;
    stage = 0;

    //Menu music
    sound.music3.setLoop(true);
    sound.music3.setVolume(25);
    sound.playMenu();
}

void Menu::Up() {
    if(selected > 0){
        menu[selected].setFillColor(sf::Color::White);
        selected--;
        menu[selected].setFillColor(sf::Color::Red);
    }
}

void Menu::Down() {
    if(selected < 2){
        menu[selected].setFillColor(sf::Color::White);
        selected++;
        menu[selected].setFillColor(sf::Color::Red);
    }
}

void Menu::Main(){
    menu.resize(4);
    menu[3].setFont(titleFont);
    menu[3].setString("Creatris");
    menu[3].setFillColor(sf::Color((rand() % 255), (rand() % 255), (rand() % 255)));
    menu[3].setPosition(550, 100);
    menu[3].setCharacterSize(200);

    for(int i; i <= 2; i++){
        menu[i].setFont(menuFont);
        menu[i].setCharacterSize(100);
        menu[i].setPosition(800, 400 +(i*100));
    }

    menu[0].setString("Play");
    menu[1].setString("Options");
    menu[2].setString("Quit");

    menu[0].setFillColor(sf::Color::Red);
    menu[1].setFillColor(sf::Color::White);
    menu[2].setFillColor(sf::Color::White);
}

void Menu::Options() {
    menu.resize(3);
    for(int i; i <= 2; i++){
        menu[i].setFont(menuFont);
        menu[i].setCharacterSize(100);
        menu[i].setPosition(800, 400 +(i*100));
    }
    menu[0].setString("Volume");
    menu[1].setString("Resolution");
    menu[2].setString("Back");

    menu[0].setFillColor(sf::Color::Red);
    menu[1].setFillColor(sf::Color::White);
    menu[2].setFillColor(sf::Color::White);

}

void Menu::PlayerDead() {
    menu.resize(4);
    menu[3].setFont(titleFont);
    menu[3].setString("You died");
    menu[3].setFillColor(sf::Color::Red);

    for(int i; i <= 2; i++){
        menu[i].setFont(menuFont);
        menu[i].setCharacterSize(100);
        menu[i].setPosition(800, 400 +(i*100));
    }
    menu[0].setString("Play again");
    menu[1].setString("Main menu");
    menu[2].setString("Quit");

    menu[0].setFillColor(sf::Color::Red);
    menu[1].setFillColor(sf::Color::White);
    menu[2].setFillColor(sf::Color::White);

}

void Menu::Volume(sf::RenderWindow &window) {
    std::fstream fs;
    std::string line;

    int volume = 50;
    //Open if exists, create if not
    fs.open("config/settings.txt", std::ios::out | std::ios::app);
    fs.close();
    fs.open("config/settings.txt", std::ios::in | std::ios::out | std::ios::app);
    while(std::getline(fs, line)){
        if(line == "volume"){
            fs >> volume;
        }
        else{
            fs << "volume" << std::endl;
            fs << volume << std::endl;
        }
    }

    sf::RectangleShape slider;
    sf::RectangleShape bar;

    slider.setSize(sf::Vector2f(20, 60));
    slider.setOrigin(20/2, 60/2);

    bar.setSize(sf::Vector2f(400, 40));
    bar.setOrigin(400/2, 40/2);

    bar.setPosition(960, 540);
    slider.setFillColor(sf::Color::Red);
}