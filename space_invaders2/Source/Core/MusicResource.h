#ifndef MUSICRESOURCE_H
#define MUSICRESOURCE_H

#include "SFML/Audio.hpp"

class MusicResource
{
private:
    // Variables
    sf::Music music;
    bool musicPaused;
    bool musicOnOff;
    bool gameMode;
    bool soundsOnOff;
    sf::SoundBuffer playerLaserSoundBuffer;
    sf::SoundBuffer playerExplosionSoundBuffer;
    sf::Sound playerLaserSound;
    sf::Sound playerExplosionSound;

public:
    MusicResource();
    void playMusic();
    void stopMusic();
    bool isMusicPaused();
    bool isSoundOn();
    void playPlayerLaserSound();
    void playPlayerExplosionSound();
    void playSound();
    void stopSound();
};

#endif