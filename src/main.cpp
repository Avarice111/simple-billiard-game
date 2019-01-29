#include "SDL.h"

#include "../include/Game.h"

Game *game = nullptr;

int main(int argc, char *argv[]) {
	const int FPS = 60.0f;
	const int DELAY_TIME = 1000.0f / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->Init("Billiard Game", 1024, 768);

	while (game->running()) {

		frameStart = SDL_GetTicks();

		game->HandleEvents();
		game->Update();
		game->Render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameTime < DELAY_TIME)

		{

			SDL_Delay((int)(DELAY_TIME - frameTime));

		}
	}


	return 0;
}