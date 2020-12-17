//
// Created by Aadne on 12.12.2020.
//

#include "ContactListener.h"

//This function check fixture user data to identify the colliding fixtures
//Player = 2
//Feet = 3
//Player right side sensor = 4
//Player left side sensor = 5
//Necromancer = 6
//Necro sensor = 7
//Bat = 8
//Bat sensor = 9
//Wolf = 10
//Wolf sensor = 11
//NecroBall = 15
//Arrow = 20


ContactListener::ContactListener() {
    footContact = 0;
}

void ContactListener::BeginContact(b2Contact *contact) {
    auto fixtureUserDataA = contact->GetFixtureA()->GetUserData();
    auto fixtureUserDataB = contact->GetFixtureB()->GetUserData();


    if(fixtureUserDataA.pointer != 0){

        //Player feet
        if (*(int*)fixtureUserDataA.pointer == 3 ){
            footContact++;
        }

        //Player sword reach sensor, right side
        if (*(int*)fixtureUserDataA.pointer == 4 ){
            b2Body* enemy = contact->GetFixtureB()->GetBody();
            //Look for enemy in vector
            if( std::find(enemiesRight.begin(), enemiesRight.end(), enemy) == enemiesRight.end() ){
                //Didn't find it already in vector so add it
                enemiesRight.push_back(enemy);
            }
        }

        //Player sword reach sensor, right side
        if (*(int*)fixtureUserDataA.pointer == 5 ){
            b2Body* enemy = contact->GetFixtureB()->GetBody();
            if( std::find(enemiesLeft.begin(), enemiesLeft.end(), enemy) == enemiesLeft.end() ){
                enemiesLeft.push_back(enemy);
            }
        }

        //Destroy physical arrow after contact
        if (*(int*)fixtureUserDataA.pointer == 20){
            b2Body* arrow = contact->GetFixtureB()->GetBody();
            bodiesToDestroy.push_back(arrow);
            if(*(int*)fixtureUserDataB.pointer == 6 | *(int*)fixtureUserDataB.pointer == 8 | *(int*)fixtureUserDataB.pointer == 10){
                b2Body* enemy = contact->GetFixtureB()->GetBody();
                bodiesToDestroy.push_back(enemy);
            }
        }

        //Necromancer sensor
        if (*(int*)fixtureUserDataA.pointer == 7){
            b2Body* necroBody = contact->GetFixtureA()->GetBody();
            auto find = necroBodyObject.find(necroBody);
            //Find the class object associated with that necro body
            //If he sees player
            if(fixtureUserDataB.pointer != 0){
                b2Body* spottedBody = contact->GetFixtureB()->GetBody();
                find->second->bodiesSeen.push_back(spottedBody);
                if(*(int*)fixtureUserDataB.pointer == 2){
                    find->second->playerClose = true;
                }
            }
        }

        //Necromancer fireball, destroy on impact
        if (*(int*)fixtureUserDataA.pointer == 15){
            b2Body* ball = contact->GetFixtureA()->GetBody();
            bodiesToDestroy.push_back(ball);
            if(fixtureUserDataB.pointer != 0){
                //If he hits player, take one heart away
                if (*(int*)fixtureUserDataB.pointer == 2){
                    //Hurt player
                    b2Body* playerBody = contact->GetFixtureB()->GetBody();
                    auto player = playerBodyObject.find(playerBody);
                    player->second->changeHealth(-1);
                }
            }
        }

        //Leaving boundaries
        if (*(int*)fixtureUserDataA.pointer == 30 ){
            b2Body* entity = contact->GetFixtureB()->GetBody();
            if(fixtureUserDataB.pointer != 0){
                bodiesToDestroy.push_back(entity);
            }
        }
    }

    //Check other fixture
    if(fixtureUserDataB.pointer != 0){

        //Player feet
        if (*(int*)fixtureUserDataB.pointer == 3 ){
            footContact++;
        }

        //Player sword reach sensor, right side
        if (*(int*)fixtureUserDataB.pointer == 4 ){
            b2Body* enemy = contact->GetFixtureB()->GetBody();
            //Look for enemy in vector
            if( std::find(enemiesRight.begin(), enemiesRight.end(), enemy) == enemiesRight.end() ){
                //Didn't find it already in vector so add it
                enemiesRight.push_back(enemy);
            }
        }

        //Player sword reach sensor, left side
        if (*(int*)fixtureUserDataB.pointer == 5 ){
            b2Body* enemy = contact->GetFixtureB()->GetBody();
            //Look for enemy in vector
            if( std::find(enemiesLeft.begin(), enemiesLeft.end(), enemy) == enemiesLeft.end() ){
                //Didn't find it already in vector so add it
                enemiesLeft.push_back(enemy);
            }
        }

        //Destroy physical arrow after contact
        if (*(int*)fixtureUserDataB.pointer == 20 ){
            b2Body* arrow = contact->GetFixtureB()->GetBody();
            bodiesToDestroy.push_back(arrow);
            if(*(int*)fixtureUserDataA.pointer == 6 | *(int*)fixtureUserDataA.pointer == 8 | *(int*)fixtureUserDataA.pointer == 10){
                b2Body* enemy = contact->GetFixtureA()->GetBody();
                bodiesToDestroy.push_back(enemy);
            }
        }

        //Necromancer sensor
        if (*(int*)fixtureUserDataB.pointer == 7){
            b2Body* necroBody = contact->GetFixtureB()->GetBody();
            auto find = necroBodyObject.find(necroBody);
            if(fixtureUserDataA.pointer != 0){
                b2Body* spottedBody = contact->GetFixtureA()->GetBody();
                find->second->bodiesSeen.push_back(spottedBody);
                if(*(int*)fixtureUserDataA.pointer == 2){
                    find->second->playerClose = true;
                }
            }
        }

        //Necromancer fireball, destroy on impact
        if (*(int*)fixtureUserDataB.pointer == 15){
            b2Body* ball = contact->GetFixtureB()->GetBody();
            bodiesToDestroy.push_back(ball);
            if(fixtureUserDataA.pointer != 0){
                //If he hits player, take one heart away
                if (*(int*)fixtureUserDataA.pointer == 2){
                    //Hurt player
                    b2Body* playerBody = contact->GetFixtureA()->GetBody();
                    auto player = playerBodyObject.find(playerBody);
                    player->second->changeHealth(-1);
                }
            }
        }

        //Leaving boundaries
        if (*(int*)fixtureUserDataB.pointer == 30 ){
            b2Body* entity = contact->GetFixtureA()->GetBody();
            if(fixtureUserDataA.pointer != 0){
                bodiesToDestroy.push_back(entity);
            }
        }
    }
}


//ENDING CONTACT
void ContactListener::EndContact(b2Contact *contact) {
    auto fixtureUserDataA = contact->GetFixtureA()->GetUserData();
    auto fixtureUserDataB = contact->GetFixtureB()->GetUserData();

    if(fixtureUserDataA.pointer != 0){

        //Player feet
        if (*(int*)fixtureUserDataA.pointer == 3 ){
            footContact--;
        }

        //Player sword reach sensor, right side
        if (*(int*)fixtureUserDataA.pointer == 4 ){
            b2Body* enemy = contact->GetFixtureB()->GetBody();
            enemiesRight.erase(std::remove(enemiesRight.begin(), enemiesRight.end(), enemy), enemiesRight.end());
        }

        //Player sword reach sensor, left side
        if (*(int*)fixtureUserDataA.pointer == 5 ){
            b2Body* enemy = contact->GetFixtureB()->GetBody();
            enemiesLeft.erase(std::remove(enemiesLeft.begin(), enemiesLeft.end(), enemy), enemiesLeft.end());
        }

        //Necromancer sensor
        if (*(int*)fixtureUserDataA.pointer == 7){
            b2Body* necroBody = contact->GetFixtureA()->GetBody();
            auto find = necroBodyObject.find(necroBody);
            auto vector = find->second->bodiesSeen;
            //If he stops seeing player
            if(fixtureUserDataB.pointer != 0){
                auto entity = contact->GetFixtureB()->GetBody();
                vector.erase(std::remove(vector.begin(), vector.end(), entity), vector.end());
                if(*(int*)fixtureUserDataB.pointer == 2){
                    find->second->playerClose = false;
                }
            }
        }
    }

    //Other fixture in contact
    if(fixtureUserDataB.pointer != 0){

        //Player feet
        if (*(int*)fixtureUserDataB.pointer == 3 ){
            footContact--;
        }

        //Player sword reach sensor, right side
        if (*(int*)fixtureUserDataB.pointer == 4 ){
            b2Body* enemy = contact->GetFixtureB()->GetBody();
            enemiesRight.erase(std::remove(enemiesRight.begin(), enemiesRight.end(), enemy), enemiesRight.end());
        }

        //Player sword reach sensor, left side
        if (*(int*)fixtureUserDataB.pointer == 5 ){
            b2Body* enemy = contact->GetFixtureB()->GetBody();
            enemiesLeft.erase(std::remove(enemiesLeft.begin(), enemiesLeft.end(), enemy), enemiesLeft.end());
        }

        //Necromancer sensor
        if (*(int*)fixtureUserDataB.pointer == 7){
            b2Body* necroBody = contact->GetFixtureB()->GetBody();
            auto find = necroBodyObject.find(necroBody);
            auto vector = find->second->bodiesSeen;
            //If he stops seeing player
            if(fixtureUserDataA.pointer != 0){
                auto entity = contact->GetFixtureA()->GetBody();
                vector.erase(std::remove(vector.begin(), vector.end(), entity), vector.end());
                if(*(int*)fixtureUserDataA.pointer == 2){
                    find->second->playerClose = false;
                }
            }
        }
    }
}