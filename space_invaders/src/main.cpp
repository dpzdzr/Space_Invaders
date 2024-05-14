#include "Game.h"

int main()
{   
    Game game;

    // Game loop
    while (game.isRunning())
    {
        game.update();
        game.render();
    }

    return 0;
}