#include "../include/Game.h"

static Table* table;
static Ball* whiteBall;
static Ball* orangeBall;
static Stick* stick;

SDL_Renderer* Game::renderer = nullptr;

Game::Game() {

}

void Game::Init(const char* title, int width, int height) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		SDL_Window *window = SDL_CreateWindow(title,
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			width, height, SDL_WINDOW_SHOWN);
		renderer = SDL_CreateRenderer(window, -1, 
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		isRunning = true;
	}
	else {
		isRunning = false;
	}

	//OBIEKTY INICJALIZACJA
	table = new Table("../data/billiard_table.bmp");
	whiteBall = new Ball("../data/ball0.bmp", Ball::Circle{ 744, 279, 33 });
	orangeBall = new Ball("../data/ball1.bmp", Ball::Circle{ 200, 279, 33 });
	stick = new Stick("../data/stick.bmp");
}

void Game::HandleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_MOUSEMOTION) {
			//PRZEMIESZCZENIE SIE KIJA
			stick->Update(event.button.x, event.button.y);
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_LEFT) {
				//SILA KIJA I STRZAL
			}
		}
	}

}


void Game::Update() {
	stick->setWhiteBall_destRect(whiteBall->get());
}

void Game::Render() {
	SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	//RENDEROWANIE RZECZY
	table->Render();
	table->DebugCollidersRender();
	whiteBall->Render();
	orangeBall->Render();
	stick->RenderEx();

	SDL_RenderPresent(renderer);

}

void Game::Clean() {

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}



