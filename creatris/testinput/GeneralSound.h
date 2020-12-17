//
// Created by Aadne on 28.11.2020.
//
#include <SFML/Audio.hpp>

#ifndef SOUNDNMUSIC_GENERALSOUND_H
#define SOUNDNMUSIC_GENERALSOUND_H


class GeneralSound {
public:
    GeneralSound();

    //Sound functions for player
    void playjumpSound();
    void playswordpullSound();
    void playswordwooshSound();
    void playswordsheathSound();

    //Music functions
    void playticktock();
    void playbattleclimax();
    void playMenu();
    void musicTransition(sf::Music music1, sf::Music music2);

    //Sound for enemy 1
    void playjumpEnemy();

    //List of sounds

    //For all
    //Music
    sf::Music music1;
    sf::Music music2;
    sf::Music music3;

    //For player buffer
    sf::SoundBuffer jumpBuffer;
    sf::SoundBuffer swordpullBuffer;
    sf::SoundBuffer swordsheathBuffer;
    sf::SoundBuffer swordwooshBuffer;

    //For player sound
    sf::Sound jumpSound;
    sf::Sound swordpullSound;
    sf::Sound swordsheathSound;
    sf::Sound swordwooshSound;


    //For enemy 1 buffer
    sf::SoundBuffer jump2Buffer;

    //For enemy 1 sound
    sf::Sound jump2Sound;

};


#endif //SOUNDNMUSIC_GENERALSOUND_H
