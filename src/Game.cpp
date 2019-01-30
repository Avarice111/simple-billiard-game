#include "../include/Game.h"

static Table* table;
static Ball* whiteBall;
static Ball* orangeBall;
static Stick* stick;
enum GameState* gameState;

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

		gameState = aiming;

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
		if (event.type == SDL_MOUSEMOTION && gameState == aiming) {
			//PRZEMIESZCZENIE SIE KIJA
			stick->Update(event.button.x, event.button.y, 16);
			mouseLastPosion = SDL_Point { event.button.x, event.button.y };
			stickLastPosition = SDL_Point{ stick->get().x, stick->get().y };
			angle = stick->getAngle();
		}
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_LEFT && gameState == aiming) {
				//SILA KIJA I STRZAL
				gameState = gainingStrengh;
				stick->setGameState(Stick::gainingStrengh);
			}
			else if (event.button.button == SDL_BUTTON_LEFT && gameState == gainingStrengh) {
				gameState = shooting;
				stick->setGameState(Stick::shooting);
				stick->Update(mouseLastPosion.x, mouseLastPosion.y, 16);
			}
		}
	}

}


void Game::Update() {
	Uint32 updateStart = SDL_GetTicks();

	stick->setWhiteBall_destRect(whiteBall->get());

	if (gameState == gainingStrengh) {
		Physics::estimateStrengh(strengh, updateStart);
		stick->Update(mouseLastPosion.x, mouseLastPosion.y, updateStart);
		/*angle = Physics::estimateAngle(SDL_Point{ stickLastPosition.x, stickLastPosition.y },
			Physics::Circle{ whiteBall->get().x, whiteBall->get().y, whiteBall->get().w */
	}
	//collisions
	if (gameState == shooting) {
		stick->Update(mouseLastPosion.x, mouseLastPosion.y, updateStart);

		whiteBall->setAngle(Physics::estimateAngle(angle));
		whiteBall->setVelocity(20);
		
		/*if (stick->check_collision(SDL_Point{ stick->get().x, stick->get().y },
			Stick::Circle{ whiteBall->get().x, whiteBall->get().y, whiteBall->get().w })) {

			whiteBall->setAngle(Physics::estimateAngle(SDL_Point{ stick->get().x, stick->get().y },
				Physics::Circle{ whiteBall->get().x, whiteBall->get().y, whiteBall->get().w }));
			whiteBall->setVelocity(Physics::estimateVelocity(Game::strengh, updateStart));
		}*/

		if (table->check_collision(SDL_Rect{ 86,0,398,52 },
			Table::Circle{ whiteBall->get().x, whiteBall->get().y, whiteBall->get().w / 2 })) {
				std::cout << "Collision1!" << std::endl;
				/*whiteBall->setAngle(Physics::estimateBounceAngle(table->get(),
					Physics::Circle{ whiteBall->get().x, whiteBall->get().y, whiteBall->get().w }));*/
		}

		if (table->check_collision(SDL_Rect{ 538,0,398,52 },
			Table::Circle{ whiteBall->get().x, whiteBall->get().y, whiteBall->get().w / 2 })) {
			std::cout << "Collision2!" << std::endl;
			/*whiteBall->setAngle(Physics::estimateBounceAngle(table->get(),
				Physics::Circle{ whiteBall->get().x, whiteBall->get().y, whiteBall->get().w }));*/
		}

		if (table->check_collision(SDL_Rect{ 0,86,52,394 },
			Table::Circle{ whiteBall->get().x, whiteBall->get().y, whiteBall->get().w / 2 })) {
			std::cout << "Collision3!" << std::endl;
		}

		if (table->check_collision(SDL_Rect{ 972,86,1024,394 },
			Table::Circle{ whiteBall->get().x, whiteBall->get().y, whiteBall->get().w / 2 })) {
			std::cout << "Collision4!" << std::endl;
		}

		if (table->check_collision(SDL_Rect{ 86,519,398,52 },
			Table::Circle{ whiteBall->get().x, whiteBall->get().y, whiteBall->get().w / 2 })) {
			std::cout << "Collision5!" << std::endl;
		}

		if (table->check_collision(SDL_Rect{ 538,519,398,52 },
			Table::Circle{ whiteBall->get().x, whiteBall->get().y, whiteBall->get().w / 2 })) {
			std::cout << "Collision6!" << std::endl;
		}
	}
	whiteBall->Update();
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



