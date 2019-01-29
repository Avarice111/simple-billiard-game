#pragma once

#include "Game.h"

class Ball {

public:
	struct Circle {
		int x, y;
		int r;
	};

	Ball(const std::string texturepath, Circle circle);
	bool check_collision(SDL_Point collision_point, Circle circle);
	bool check_collision(SDL_Rect rect, Circle);
	void Update();
	void Render();
	SDL_Rect get();

private:
	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;
};