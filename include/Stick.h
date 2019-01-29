#pragma once

#include "Game.h"

class Stick {

public:
	Stick(const std::string texturepath);
	void Update(int mouse_x, int mouse_y);
	void RenderEx();
	void Render();
	void setWhiteBall_destRect(SDL_Rect whiteBall_destRect);

	SDL_Rect get();

private:
	double Angle(int x1, int y1, int x2, int y2);
	//double AngleRad(int x1, int y1, int x2, int y2);
	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;

	SDL_Rect whiteBall_destRect;
	SDL_Point point;
	double angle;
};

