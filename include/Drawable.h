#pragma once

#include "Game.h"

class Drawable {

public:
	static SDL_Texture* LoadTexture(const std::string texturePath);
	static void Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest);
};