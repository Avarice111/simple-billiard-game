#pragma once

#include "Game.h"

class Ball {

public:
	Ball(const std::string texturepath, int x, int y);
	void Update();
	void Render();
	SDL_Rect get();

private:
	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;
};