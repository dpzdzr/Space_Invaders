#include "MusicResource.h"

MusicResource::MusicResource() : musicOnOff(true), musicPaused(false), soundsOnOff(true)
{
    music.openFromFile(RESOURCES "Sounds/music.ogg");
    music.setLoop(true);
    musicPaused = false;

    playerLaserSoundBuffer.loadFromFile(RESOURCES "Sounds/laser.ogg");
    playerLaserSound.setBuffer(playerLaserSoundBuffer);

    playerExplosionSoundBuffer.loadFromFile(RESOURCES "Sounds/explosion.ogg");
    playerExplosionSound.setBuffer(playerExplosionSoundBuffer);
}

void MusicResource::playMusic()
{
    if (musicOnOff)
    {
        music.play();
        musicPaused = false;
    }
}

void MusicResource::stopMusic()
{
    if (musicOnOff)
    {
        music.pause();
        musicPaused = true;
    }
}

bool MusicResource::isMusicPaused()
{
    return musicPaused;
}

bool MusicResource::isSoundOn()
{
    return soundsOnOff;
}

void MusicResource::playPlayerLaserSound()
{
    playerLaserSound.play();
}

void MusicResource::playPlayerExplosionSound()
{
    playerExplosionSound.play();
}

void MusicResource::playSound()
{
    playerLaserSound.setVolume(100);
    playerExplosionSound.setVolume(100);
    soundsOnOff = true;
}

void MusicResource::stopSound()
{
    playerLaserSound.setVolume(0);
    playerExplosionSound.setVolume(0);
    soundsOnOff = false;
}
