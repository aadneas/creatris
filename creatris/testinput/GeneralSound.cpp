//
// Created by Aadne on 28.11.2020.
//

#include "GeneralSound.h"

GeneralSound::GeneralSound() {
    //Player load buffer
    jumpBuffer.loadFromFile("sounds/jump.wav");
    swordpullBuffer.loadFromFile("sounds/swordpulled.wav");
    swordsheathBuffer.loadFromFile("sounds/swordsheathed.wav");
    swordwooshBuffer.loadFromFile("sounds/swordwoosh.wav");

    //Player set sound
    jumpSound.setBuffer(jumpBuffer);
    swordpullSound.setBuffer(swordpullBuffer);
    swordsheathSound.setBuffer(swordsheathBuffer);
    swordwooshSound.setBuffer(swordwooshBuffer);

    //Enemy 1 load buffer
    jump2Buffer.loadFromFile("sounds/boing.wav");

    //Enemy 1 set sound
    jump2Sound.setBuffer(jump2Buffer);

    //Music
    music1.openFromFile("music/ticktocklooping.wav");
    music2.openFromFile("music/battleclimax.wav");
    music3.openFromFile("music/menu.wav");

    music1.setVolume(25);
    music2.setVolume(25);
}



void GeneralSound::playjumpSound(){
    if(jumpSound.getStatus() == 2)
        return;

    jumpSound.play();
}

void GeneralSound::playswordpullSound(){
    if(swordpullSound.getStatus() == 2)
        return;

    swordpullSound.play();
}

void GeneralSound::playswordsheathSound(){
    if(swordsheathSound.getStatus() == 2)
        return;

    swordsheathSound.play();
}

void GeneralSound::playswordwooshSound(){
    //if(swordwooshSound.getStatus() == 2)
        //return;

    swordwooshSound.play();
}

void GeneralSound::playticktock(){
    if(music1.getStatus() == 2){
        music1.pause();
        return;
    }


    music1.play();
}

void GeneralSound::playbattleclimax(){
    if(music2.getStatus() == 2){
        music2.pause();
        return;
    }

    music2.play();
}

void GeneralSound::playMenu(){
    if(music3.getStatus() == 2){
        music3.pause();
        return;
    }

    music3.play();
}

void GeneralSound::playjumpEnemy() {
    if(jump2Sound.getStatus() == 2){
        return;
    }
    jump2Sound.play();
}

void GeneralSound::musicTransition(sf::Music music1, sf::Music music2){
    //
}