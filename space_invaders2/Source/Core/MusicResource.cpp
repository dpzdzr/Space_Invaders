#include "MusicResource.h"

MusicResource::MusicResource() : musicOn(true)
{
    music.openFromFile(RESOURCES "Sounds/music.ogg");
    music.setLoop(true);
    musicPaused = false;
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
