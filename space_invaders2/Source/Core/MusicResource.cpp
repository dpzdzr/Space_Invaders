#include "MusicResource.h"

MusicResource::MusicResource() : musicOn(true)
{
    music.openFromFile(RESOURCES "Sounds/music.ogg");
    music.setLoop(true);
    musicPaused = false;
    playerLaserSoundBuffer.loadFromFile(RESOURCES "Sounds/laser.ogg");
    playerLaserSound.setBuffer(playerLaserSoundBuffer);
}

void MusicResource::playMusic()
{
    if (musicOn)
    {
        music.play();
        musicPaused = false;
    }
}

void MusicResource::stopMusic()
{
    if (musicOn)
    {
        music.pause();
        musicPaused = true;
    }
}

bool MusicResource::getMusicStatus()
{
    return musicPaused;
}

void MusicResource::playPlayerLaserSound()
{
    playerLaserSound.play();
}