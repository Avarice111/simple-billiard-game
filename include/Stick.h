#pragma once

#include "Game.h"

class Stick {

public:
	struct Circle {
		int x, y;
		int r;
	};

	enum GameState {
		aiming,
		gainingStrengh,
		shooting
	};

	Stick(const std::string texturepath);
	void setWhiteBall_destRect(SDL_Rect whiteBall_destRect);
	void setGameState(GameState gamesState);
	bool check_collision(SDL_Point collision_point, Circle circle);
	void Update(int mouse_x, int mouse_y, Uint32 lastTime);
	void RenderEx();
	void Render();

	SDL_Rect get();
	int getStrengh();
	double getAngle();

private:
	double Angle(int x1, int y1, int x2, int y2);

	//double AngleRad(int x1, int y1, int x2, int y2);
	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;

	SDL_Rect whiteBall_destRect;
	SDL_Point point;
	double angle;

	double velocity;

	int strengh;

	enum GameState gameState;
};

