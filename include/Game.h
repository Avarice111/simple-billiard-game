#ifndef  Game_hpp
#define  Game_hpp

#include "SDL.h"

#include <stdexcept>
#include <stdexcept>
#include <memory>
#include <string>
#include <set>
#include <tuple>
#include <iostream>
#include <cstdint>
#include <vector>
#include <array>
#include <math.h>

#include "../include/Physics.h"

#include "../include/Ball.h"
#include "../include/Table.h"
#include "../include/Stick.h"

class Game {

public:
	static const int FPS = 60.0f;
	static const int DELAY_TIME = 1000.0f / FPS;

	enum GameState {
		aiming,
		gainingStrengh,
		shooting
	};

	Game();
	void Init(const char* title, int width, int height);
	void HandleEvents();
	void Update();
	void Render();
	void Clean();

	bool running() { return isRunning; }
	static SDL_Renderer *renderer;

private:
	double strengh;
	int cnt = 0;
	SDL_Point mouseLastPosion;
	bool isRunning;
	SDL_Window *window;
	enum GameState gameState;
	double angle;
	SDL_Point stickLastPosition;
};


#endif
