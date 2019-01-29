#include "../include/Ball.h"
#include "../include/Drawable.h"

Ball::Ball(const std::string texturepath, int x, int y) {
	//TEKSTURA I ZMIENNE
	texture = Drawable::LoadTexture(texturepath);
	srcRect.w = 405;
	srcRect.h = 405;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.w = 33;
	destRect.h = 33;
	destRect.x = x - destRect.w / 2;
	destRect.y = y - destRect.h / 2;
}

void Ball::Update() {
	//UPDATE EVERY FRAME

}

void Ball::Render() {
	SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
}

SDL_Rect Ball::get() {
	return destRect;
}
