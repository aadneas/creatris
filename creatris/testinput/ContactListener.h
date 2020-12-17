//
// Created by Aadne on 12.12.2020.
//

#ifndef TESTINPUT_CONTACTLISTENER_H
#define TESTINPUT_CONTACTLISTENER_H

#include "Box2d/include/box2d/box2d.h"
#include "GlobalVariables.h"
#include <vector>
#include <algorithm>
#include "Player.h"

//Player and enemies
#include "Enemy1.h"

class ContactListener : public b2ContactListener {
public:
    ContactListener();

    void BeginContact(b2Contact* contact);

    void EndContact(b2Contact* contact);

    //To tell when player is touching ground
    int footContact;
};


#endif //TESTINPUT_CONTACTLISTENER_H
