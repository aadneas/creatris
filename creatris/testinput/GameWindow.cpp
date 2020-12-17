//
// Created by Aadne on 01.12.2020.
//

#include "GameWindow.h"




GameWindow::GameWindow():
        window(sf::VideoMode(1920, 1080), "Game")
{
    //Window
    window.setFramerateLimit(60);
    deltaTime = 0.0f;

    mainMenu = 1;
}

void GameWindow::RunningGame(){
    //Player input
    Input input;

    //Debug Box2D
    SFMLDebugDraw debugDraw(window);

    //TESTING DELETE
    auto * necro = new Enemy1(&world, b2Vec2(600, 400));
    necroVector.push_back(necro);
    necroBodyObject.emplace(necro->body, necro);


    while(window.isOpen()){

        while(mainMenu == 1){
            window.clear(sf::Color::Black);
            mainMenu = input.menu_input(window);
            window.display();
        }


        deltaTime = clock.restart().asSeconds();

        //Physics
        world.Step(1.0f/30, 8, 3);

        input.player_input2(window, deltaTime);



        //Debug box2d draw
        world.SetDebugDraw(&debugDraw);
        debugDraw.SetFlags(b2Draw::e_shapeBit);

        //Behavior
        if(!necroBodyObject.empty()){
            for(auto i : necroBodyObject){
                i.second->Behavior(deltaTime);
            }
        }
        if(!batBodyObject.empty()){
            for(auto i : batBodyObject){
                i.second->Behavior(deltaTime);
            }
        }
        if(!wolfBodyObject.empty()){
            for(auto i : wolfBodyObject){
                i.second->Behavior(deltaTime);
            }
        }


        //Display and draw
        window.clear(sf::Color::Blue);

        //Fireball behaviors and draw
        if(!ballVector.empty()){
            for(auto ball : ballVector){
                ball->Fly(deltaTime);
                window.draw(ball->ball);
            }
        }

        //Drawing enemies
        if(!necroBodyObject.empty()){
            for(auto i : necroBodyObject){
                window.draw(i.second->shape);
            }
        }
        if(!batBodyObject.empty()){
            for(auto i : batBodyObject){
                window.draw(i.second->shape);
            }
        }
        if(!wolfBodyObject.empty()){
            for(auto i : wolfBodyObject){
                window.draw(i.second->shape);
            }
        }


        //Drawing arrows
        for(auto i : arrowVector){
            i->arrow.setPosition(i->arrowCol->GetPosition().x * 30, i->arrowCol->GetPosition().y * 30);
            i->arrow.setRotation(i->arrowCol->GetAngle() * (180/M_PI));
            window.draw(i->arrow);
        }

        window.draw(input.player->shape);
        for(auto i : input.player->heart){
            window.draw(i);
        }

        //Debug
        world.DebugDraw();
        window.display();

        //Shiva, the destroyer (Move to his own class?)
        if(!bodiesToDestroy.empty()){
            for(auto it : bodiesToDestroy){
                //What type is to be destroyed?
                //Arrow?
                if(arrowBodyObject.find(it) != arrowBodyObject.end()){
                    auto find = arrowBodyObject.find(it);
                    //Also remove from drawing vector
                    arrowVector.erase(std::remove(arrowVector.begin(), arrowVector.end(), find->second), arrowVector.end());
                    delete find->second;
                    //Erase from the body to object map
                    arrowBodyObject.erase(find);
                }
                    //Fireball?
                else if(ballBodyObject.find(it) != ballBodyObject.end()){
                    auto find = ballBodyObject.find(it);
                    ballVector.erase(std::remove(ballVector.begin(), ballVector.end(), find->second), ballVector.end());
                    enemiesRight.erase(std::remove(enemiesRight.begin(), enemiesRight.end(), find->first), enemiesRight.end());
                    enemiesLeft.erase(std::remove(enemiesLeft.begin(), enemiesLeft.end(), find->first), enemiesLeft.end());
                    delete find->second;
                    ballBodyObject.erase(find);
                }
                    //Necromancer?
                else if(necroBodyObject.find(it) != necroBodyObject.end()){
                    auto find = necroBodyObject.find(it);
                    necroVector.erase(std::remove(necroVector.begin(), necroVector.end(), find->second), necroVector.end());
                    enemiesRight.erase(std::remove(enemiesRight.begin(), enemiesRight.end(), find->first), enemiesRight.end());
                    enemiesLeft.erase(std::remove(enemiesLeft.begin(), enemiesLeft.end(), find->first), enemiesLeft.end());
                    world.DestroyBody(it);
                    it = 0;
                    delete find->second;
                    necroBodyObject.erase(find);
                }
                    //Bat?
                else if(batBodyObject.find(it) != batBodyObject.end()){
                    auto find = batBodyObject.find(it);
                    batVector.erase(std::remove(batVector.begin(), batVector.end(), find->second), batVector.end());
                    delete find->second;
                    batBodyObject.erase(find);
                }
                    //Wolf?
                else if(wolfBodyObject.find(it) != wolfBodyObject.end()){
                    auto find = wolfBodyObject.find(it);
                    wolfVector.erase(std::remove(wolfVector.begin(), wolfVector.end(), find->second), wolfVector.end());
                    delete find->second;
                    wolfBodyObject.erase(find);
                }

                //And remove body from the destroy vector then destroy the body
                bodiesToDestroy.erase(std::remove(bodiesToDestroy.begin(), bodiesToDestroy.end(), it), bodiesToDestroy.end());
                if(it != 0)
                    world.DestroyBody(it);
            }
        }
    }
}