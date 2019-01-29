#pragma once
#include "Game.h"

class Table {

public:
	Table(const std::string texturepath);
	void Render();
	void DebugCollidersRender();
	SDL_Rect get();

private:
	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;
};