#pragma once
#include "Game.h"

class Table {

public:
	struct Circle {
		int x, y;
		int r;
	};

	Table(const std::string texturepath);
	bool check_collision(SDL_Point collision_point, Circle circle);
	bool check_collision(SDL_Rect rect, Circle circle);
	void Render();
	void DebugCollidersRender();
	SDL_Rect get();

private:
	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;
};