#include "../include/Table.h"
#include "../include/Drawable.h"

Table::Table(const std::string texturepath) {
	//TEKSTURA I ZMIENNE
	texture = Drawable::LoadTexture(texturepath);
	srcRect.w = 1024;
	srcRect.h = 571;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
	destRect.x = srcRect.x;
	destRect.y = srcRect.y;

}

bool Table::check_collision(SDL_Point collision_point, Circle circle) {
	if (abs(collision_point.x - circle.x) <= circle.r &&
		abs(collision_point.y - circle.y) <= circle.r) {
		return true;
	}
	else
		return false;
}

bool Table::check_collision(SDL_Rect rect, Circle circle) {
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

void Table::Render() {
	SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
	//std::cout << "Table: Render" << std::endl;
}

void Table::DebugCollidersRender() {

	SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);

	SDL_Rect billiard_rect1 = { 86,0,398,52 };

	SDL_Rect billiard_rect2 = { 538,0,398,52 };

	SDL_Rect billiard_rect3 = { 0,86,52,394 };

	SDL_Rect billiard_rect4 = { 972,86,1024,394 };

	SDL_Rect billiard_rect5 = { 86,519,398,52 };

	SDL_Rect billiard_rect6 = { 538,519,398,52 };


	SDL_RenderDrawRect(Game::renderer, &billiard_rect1);

	SDL_RenderDrawRect(Game::renderer, &billiard_rect2);

	SDL_RenderDrawRect(Game::renderer, &billiard_rect3);

	SDL_RenderDrawRect(Game::renderer, &billiard_rect4);

	SDL_RenderDrawRect(Game::renderer, &billiard_rect5);

	SDL_RenderDrawRect(Game::renderer, &billiard_rect6);
}

SDL_Rect Table::get() {
	return destRect;
}
