//
// Created by Aadne on 15.12.2020.
//

#include "GlobalVariables.h"

//Physical world
b2World world(b2Vec2(0.0f, 10.0f));

//Objects
std::vector<Arrow*> arrowVector;    //Arrows
std::vector<NecroBall*> ballVector; //Fireballs
std::vector<Enemy1*> necroVector;   //Necromancers
std::vector<Enemy2*> batVector;     //Bats
std::vector<Enemy3*> wolfVector;    //Wolves

//Bodies to be destroyed, added from contact listener
std::vector<b2Body*> bodiesToDestroy;

//b2Body to class object associates for when clean up time comes
std::map<b2Body*, Arrow*> arrowBodyObject;
std::map<b2Body*, Enemy1*> necroBodyObject;
std::map<b2Body*, Enemy2*> batBodyObject;
std::map<b2Body*, Enemy3*> wolfBodyObject;
std::map<b2Body*, NecroBall*> ballBodyObject;
std::map<b2Body*, Player*> playerBodyObject;

//These vectors will tell which enemies are within reach of player sword
//One for each cone
std::vector<b2Body*> enemiesLeft;
std::vector<b2Body*> enemiesRight;


