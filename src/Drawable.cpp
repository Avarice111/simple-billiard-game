#include "../include/Drawable.h"

SDL_Texture* Drawable::LoadTexture(const std::string texturePath) {
	SDL_Surface *bmp = SDL_LoadBMP(texturePath.c_str());
	SDL_Texture *texture = SDL_CreateTextureFromSurface(Game::renderer, bmp);
	SDL_FreeSurface(bmp);

	return texture;
}



void Drawable::Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest){
	SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}