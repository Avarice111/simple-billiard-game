#include "SDL.h"

#include "../include/Game.h"

Game *game = nullptr;

int main(int argc, char *argv[]) {
	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->Init("Billiard Game", 1024, 768);

	while (game->running()) {

		frameStart = SDL_GetTicks();

		game->HandleEvents();
		game->Update();
		game->Render();

		frameTime = frameStart - SDL_GetTicks();

		if (frameTime < Game::DELAY_TIME)

		{

			SDL_Delay((int)(Game::DELAY_TIME - frameTime));

		}
	}


	return 0;
}