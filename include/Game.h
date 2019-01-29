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

#include "../include/Ball.h"
#include "../include/Table.h"
#include "../include/Stick.h"

class Game {

public:
	Game();
	void Init(const char* title, int width, int height);
	void HandleEvents();
	void Update();
	void Render();
	void Clean();

	bool running() { return isRunning; }
	static SDL_Renderer *renderer;

private:

	int cnt = 0;
	bool isRunning;
	SDL_Window *window;
};


#endif
