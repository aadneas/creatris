//
// Created by Aadne on 15.12.2020.
//
#include "Box2d/include/box2d/box2d.h"
#include <vector>
#include <fstream>
#include <map>

#ifndef TESTINPUT_GLOBALVARIABLES_H
#define TESTINPUT_GLOBALVARIABLES_H

class Arrow;
class Enemy1;
class Enemy2;
class Enemy3;
class NecroBall;
class Player;

//Physical world
extern b2World world;

//Vector with objects on screen
extern std::vector<Arrow*> arrowVector;    //Arrows
extern std::vector<NecroBall*> ballVector; //Fireballs
extern std::vector<Enemy1*> necroVector;   //Necromancers
extern std::vector<Enemy2*> batVector;     //Bats
extern std::vector<Enemy3*> wolfVector;    //Wolves

//Arrows or dead enemies or dead player
extern std::vector<b2Body*> bodiesToDestroy;

//The class object associated with the b2Body so that when you clean you can delete both
extern std::map<b2Body*, Arrow*> arrowBodyObject;
extern std::map<b2Body*, Enemy1*> necroBodyObject;
extern std::map<b2Body*, Enemy2*> batBodyObject;
extern std::map<b2Body*, Enemy3*> wolfBodyObject;
extern std::map<b2Body*, NecroBall*> ballBodyObject;
extern std::map<b2Body*, Player*> playerBodyObject;

//These vectors will tell which enemies are within reach of player sword
//One for each cone
extern std::vector<b2Body*> enemiesLeft;
extern std::vector<b2Body*> enemiesRight;


#endif //TESTINPUT_GLOBALVARIABLES_H
