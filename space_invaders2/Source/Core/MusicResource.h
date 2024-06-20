#ifndef MUSICRESOURCE_H
#define MUSICRESOURCE_H

#include "SFML/Audio.hpp"

class MusicResource
{
private:
    // Variables
    sf::Music music;
    bool musicPaused;
    bool musicOn;
    bool gameMode;

public:
    MusicResource();
    void playMusic();
    void stopMusic();
    bool getMusicStatus();
};

#endif