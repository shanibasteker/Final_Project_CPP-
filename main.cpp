//311318075
//shanibasteker@gmail.com

#include "Game.h"

int main(int argc, char* argv[])
{
	// Generate Random Seed
	srand(time(0));

	// Start Game
	Game* game = new Game();
	game->initialize();

	while (game->isRunning())
	{	
		game->ManageEvents();
		game->update();

		if (game->isRunning())
			game->render();
	}

	// Clean Game
	game->clean();
	delete game;

	return 0;
}
