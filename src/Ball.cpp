#include "../include/Ball.h"
#include "../include/Drawable.h"

Ball::Ball(const std::string texturepath, Circle circle) {
	//TEKSTURA I ZMIENNE
	texture = Drawable::LoadTexture(texturepath);
	srcRect.w = 405;
	srcRect.h = 405;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.w = circle.r;
	destRect.h = circle.r;
	destRect.x = circle.x - destRect.w / 2;
	destRect.y = circle.y - destRect.h / 2;
}

bool Ball::check_collision(SDL_Point collision_point, Circle circle) {
	if (abs(collision_point.x - circle.x) <= circle.r &&
		abs(collision_point.y - circle.y) <= circle.r) {
		return true;
	}
	else
		return false;
}

bool Ball::check_collision(SDL_Rect rect, Circle circle) {
	int rightSide = rect.x + rect.w;
	int leftSide = rect.x;
	int topSide = rect.y;
	int bottomSide = rect.x + rect.h;

	if ((rightSide - circle.x < circle.r ||
		circle.x - leftSide < circle.r) &&
		(bottomSide - circle.y < circle.r ||
		circle.y - topSide < circle.r)) {
		return true;
	}
	else
		return false;
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
