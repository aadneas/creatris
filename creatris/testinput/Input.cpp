//
// Created by Aadne on 01.12.2020.
//

#include "Input.h"
#include <iostream>

Input::Input(){
    playerBodyObject.emplace(player->playerCol, player);

    //Animation.Update parameters
    cycleStart.x = 0;
    cycleStart.y = 0;
    cycleCount = 4;

    //Passing information from player class to animation class
    animation.frameCount = player->frameCount;
    animation.switchTime = player->switchTime;
    animation.uvRect.width = player->playerTexture.getSize().x / float(player->frameCount.x);
    animation.uvRect.height = player->playerTexture.getSize().y / float(player->frameCount.y);

    //Check whether certain animations are in process so not to interrupt them
    inProcess = false;
    fullAnimation = false;
    blockMovement = false;
    //

    //Cycle through all the sword swinging animations
    //This will make it play 1 full animation if there is 1 input, but also
    //cycle through different animation if key is continually pressed
    swordSwingCycle = 0;

    //Debounce
    debounceTime = 0.0f;

    //Slow move speed if crouched
    speedDivider = 1;

    //Bool keys
    a = false;
    d = false;
    w = false;
    s = false;
    r = false;
    q = false;
    space = false;
    f = false;
    enter = false;

    //Released keys
    w2 = true;
    s2 = true;
    r2 = true;
    space2 = true;
    enter2 = true;


    player->shape.setOrigin(200/2, 200/2);


    //JUMP COLLISION DETECTION TESTING
    world.SetContactListener(&contact);

}


//New input
void Input::player_input2(sf::RenderWindow &window, float deltaTime) {
    physics.velocity.x = 0;
    physics.velocity.y = 0;

    currentSpeed = player->playerCol->GetLinearVelocity();

    while (window.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            window.close();
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::D)
            {
                d = true;
            }

            if (event.key.code == sf::Keyboard::A)
            {
                a = true;
            }

            if (event.key.code == sf::Keyboard::W)
            {
                w = true;
            }

            if (event.key.code == sf::Keyboard::S)
            {
                s = true;
            }

            if (event.key.code == sf::Keyboard::R && r2){
                r = true;
                r2 = false;
            }

            if (event.key.code == sf::Keyboard::Q)
            {
                q = true;
            }

            if (event.key.code == sf::Keyboard::Space && space2){
                space = true;
                space2 = false;
            }

            if (event.key.code == sf::Keyboard::F)
            {
                f = true;
            }

        }
        else if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::D)
            {
                d = false;
            }

            if (event.key.code == sf::Keyboard::A)
            {
                a = false;
            }

            if (event.key.code == sf::Keyboard::W)
            {
                w = false;
            }

            if (event.key.code == sf::Keyboard::S)
            {
                s = false;
                speedDivider = 1;
            }

            if (event.key.code == sf::Keyboard::R){
                r = false;
                r2 = true;
            }

            if (event.key.code == sf::Keyboard::Q)
            {
                q = false;
                swordSwingCycle = 0;
            }

            if (event.key.code == sf::Keyboard::Space){
                space = false;
                space2 = true;
            }

            if (event.key.code == sf::Keyboard::F)
            {
                f = false;
                deltaTime = 0;
                blockMovement = false;
            }

        }

    }

    //Setting movement magnitude but only do it if movement is not blocked or if you are in the air
    if(!blockMovement || !contact.footContact){
        if (d){
            physics.velocity.x += player->speed * deltaTime;
        }
        if (a){
            physics.velocity.x -= player->speed * deltaTime;
        }
        if (s){
            speedDivider = 2;
        }
    }

    //Movement animation. These animations should only play if no other animation is in process
    //and you are on the ground
    if(!inProcess && contact.footContact){
        //
        //Run left and right
        if(a || d){
            if(!player->sword) {
                cycleCount = 6;
                cycleStart.x = 1;
                cycleStart.y = 1;
            }
            else {
                cycleCount = 6;
                cycleStart.x = 4;
                cycleStart.y = 15;
            }
        }

        //
        //Crouch
        if(s){
            cycleCount = 4;
            cycleStart.x = 4;
            cycleStart.y = 0;
            //Moving while crouched
            if(a || d){
                cycleCount = 6;
                cycleStart.x = 4;
                cycleStart.y = 18;
            }
        }

        //Pull and sheath sword
        if (r){
            player->sword = !player->sword;
            r = false;
            fullAnimation = true;
            cycleCount = 4;
            if(player->sword){
                sound.playswordpullSound();
                cycleStart.x = 6;
                cycleStart.y = 9;
            }
            else{
                sound.playswordsheathSound();
                cycleStart.x = 3;
                cycleStart.y = 10;
            }
        }

        //Sword swing
        if(q && player->sword){
            fullAnimation = true;
            sound.playswordwooshSound();
            hit_enemies(player->facingRight);
            if(swordSwingCycle == 0){
                cycleCount = 6;
                cycleStart.x = 0;
                cycleStart.y = 6;
                swordSwingCycle++;
            }
            else if(swordSwingCycle == 1){
                cycleCount = 5;
                cycleStart.x = 6;
                cycleStart.y = 6;
                swordSwingCycle = 0;
            }
        }

        //Bow
        if(f){
            cycleCount = 9;
            cycleStart.x = 3;
            cycleStart.y = 16;
            blockMovement = true;
            debounceTime += deltaTime;
            if(debounceTime >= 0.7f){
                //Shoot arrow timed with animation
                shoot_arrow(player->playerCol->GetPosition(), player->facingRight, player->arrowForce);
                debounceTime = -0.18f;
            }
        }
    }


    //Jump if space was pressed and you have contact with ground
    if(space && contact.footContact){
        space = false;
        fullAnimation = true;
        sound.playjumpSound();
        cycleCount = 6;
        cycleStart.x = 2;
        cycleStart.y = 2;
        physics.velocity.y = player->speed * 12 * deltaTime;
        impulse = physics.velocity.y * player->playerCol->GetMass();
        player->playerCol->ApplyLinearImpulseToCenter(b2Vec2(0, -impulse), true);
        debounceTime = 0;
    }

    //Falling animation
    if(!contact.footContact && currentSpeed.y >= 0){
        fullAnimation = false;
        cycleCount = 2;
        cycleStart.x = 1;
        cycleStart.y = 3;
    }
    //Front flipping on the way up after initial jump animation
    if(!contact.footContact && currentSpeed.y <= 0 && !inProcess){
        fullAnimation = false;
        cycleCount = 4;
        cycleStart.x = 4;
        cycleStart.y = 2;
    }

    //Key activated animations for when player is not grounded
    if(!contact.footContact){
        //Bow
        if(f){
            inProcess = false;
            fullAnimation = false;
            cycleCount = 6;
            cycleStart.x = 5;
            cycleStart.y = 17;
            debounceTime += deltaTime;
            if(debounceTime >= 0.5f){
                shoot_arrow(player->playerCol->GetPosition(), player->facingRight, player->arrowForce);
                debounceTime = -0.18f;
            }
        }
    }

    //Idle //CLEAN THIS
    if(!currentSpeed.x && !currentSpeed.y && !a && !d && !s && !f && !fullAnimation && contact.footContact){
        cycleCount = 4;
        cycleStart.x = 0;
        cycleStart.y = 0;
        if(player->sword){
            cycleStart.x = 3;
            cycleStart.y = 5;
        }
    }


    //System
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        window.close();

    //Flip right and left texture
    if(physics.velocity.x < 0){
        player->facingRight = false;
    }
    else if(physics.velocity.x > 0){
        player->facingRight = true;
    }


    //Animation modes
    if(fullAnimation)
        inProcess = animation.fullAnimation(deltaTime, player->facingRight, cycleCount, cycleStart);
    else
        animation.Update(deltaTime, player->facingRight, cycleCount, cycleStart);

    //Block movement while doing full animations and go back to normal when animation is done
    if(inProcess){
        blockMovement = true;
    }
    else{
        fullAnimation = false;
        blockMovement = false;
    }

    //Force
    impulse = physics.velocity.x * player->playerCol->GetMass();

    //Movement speed restriction
    if(player->facingRight){
        if(player->playerCol->GetLinearVelocity().x < (5 / speedDivider)){
            player->playerCol->ApplyLinearImpulseToCenter(b2Vec2(impulse, 0), true);
        }
    }
    else{
        if(player->playerCol->GetLinearVelocity().x > -(5 / speedDivider)){
            player->playerCol->ApplyLinearImpulseToCenter(b2Vec2(impulse, 0), true);
        }
    }

    //Moving texture and updating texture
    player->shape.setPosition(30 * player->playerCol->GetPosition().x, 30 * player->playerCol->GetPosition().y - 13);
    player->shape.setTextureRect(animation.uvRect);
}

//Shoot an arrow
void Input::shoot_arrow(b2Vec2 position, bool facingRight, int force) {
    position.x = position.x * 30;
    position.y = position.y * 30;
    auto * arrow = new Arrow(&world, position);
    arrowVector.push_back(arrow);
    arrowBodyObject.emplace(arrow->arrowCol, arrow);
    arrow->Fly(facingRight, force);
}

//Applying force to enemies when hitting them with sword
void Input::hit_enemies(bool facingRight){
    if(facingRight){
        for(auto it : enemiesRight){
            if(it->GetFixtureList()->GetUserData().pointer != 0){
                it->SetLinearVelocity(b2Vec2(0, it->GetLinearVelocity().y));
                it->ApplyLinearImpulseToCenter(b2Vec2(75, 0), true);
                b2Fixture* fixture = it->GetFixtureList();
                if(fixture->IsSensor()){
                    fixture = fixture->GetNext();
                }
                //If necromancer
                if(*(int*)fixture->GetUserData().pointer == 6){
                    auto necro = necroBodyObject.find(it);
                    necro->second->Hurt();
                }
                //Bat
                if(*(int*)it->GetFixtureList()->GetUserData().pointer == 8){
                    auto bat = necroBodyObject.find(it);
                    bat->second->Hurt();
                }
                //Wolf
                if(*(int*)it->GetFixtureList()->GetUserData().pointer == 10){
                    auto wolf = wolfBodyObject.find(it);
                    //wolf->second->Hurt();
                }
            }
        }
    }
    else{
        for(auto it : enemiesLeft){
            if(it->GetFixtureList()->GetUserData().pointer != 0){
                it->SetLinearVelocity(b2Vec2(0, it->GetLinearVelocity().y));
                it->ApplyLinearImpulseToCenter(b2Vec2(-75, 0), true);
                //If necromancer
                if(*(int*)it->GetFixtureList()->GetUserData().pointer == 6){
                    auto necro = necroBodyObject.find(it);
                    necro->second->Hurt();
                }
                //Bat
                if(*(int*)it->GetFixtureList()->GetUserData().pointer == 8){
                    auto bat = necroBodyObject.find(it);
                    bat->second->Hurt();
                }
                //Wolf
                if(*(int*)it->GetFixtureList()->GetUserData().pointer == 10){
                    auto wolf = wolfBodyObject.find(it);
                    //wolf->second->Hurt();
                }
            }
        }
    }
}

//Main menu input
int Input::menu_input(sf::RenderWindow &window) {

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return 0;
        }

        if (event.type == sf::Event::KeyPressed) {
            if ((event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) && w2) {
                w = true;
                w2 = false;
            }
            if ((event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) && s2) {
                s = true;
                s2 = false;
            }
            if (event.key.code == sf::Keyboard::Enter && enter2) {
                enter = true;
                enter2 = false;
            }
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
                return 0;
            }
        }
        else if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up) {
                w = false;
                w2 = true;
            }
            if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down) {
                s = false;
                s2 = true;
            }
            if (event.key.code == sf::Keyboard::Enter) {
                enter = false;
                enter2 = true;
            }
        }
    }

    if(w){
        menu.Up();
        w = false;
    }

    if(s){
        menu.Down();
        s = false;
    }

    if(enter){
        enter = false;
        //Main menu
        if(menu.stage == 0){
            if(menu.selected == 0){
                menu.sound.music3.stop();
                return 2;
            }
            if(menu.selected == 1){
                menu.Options();
                menu.selected = 0;
                menu.stage = 1;
            }
            if(menu.selected == 2){
                window.close();
                return 0;
            }
        }
        //Options page
        else if(menu.stage == 1){
            if(menu.selected == 0){
                //Volume
                menu.Volume(window);
            }
            if(menu.selected == 1){
                //Nothing
            }
            if(menu.selected == 2){
                menu.Main();
                menu.selected = 0;
                menu.stage = 0;
            }

        }

        else if(menu.stage == 2){
            if(menu.selected == 0){
                //Restart game
            }
            if(menu.selected == 1){
                menu.Main();
                menu.selected = 0;
                menu.stage = 0;
            }
            if(menu.selected == 2){
                window.close();
                return 0;
            }
        }

    }

    //Draw text
    for(auto i: menu.menu){
        window.draw(i);
    }

return 1;
}