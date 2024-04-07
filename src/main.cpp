#include "../inc/Game.h"

int main()
{
    // Init srand
    std::srand(static_cast<unsigned>(time(NULL)));

    // Init Game engine
    Game game;

    // Game loop
    while (game.running())
    {
        // Update
        game.update();
        // Render
        game.render();
        // Draw your game
    }

    return 0;
}