#include "Game.h"

int main()
{
	// Initilize random seed
	srand(static_cast<unsigned>(time(0)));

	// Initilize game object
	Game game;

	// Game loop
	while (game.running())
	{
		game.update();
		game.render();
	}

	// End of application

	return 0;
}