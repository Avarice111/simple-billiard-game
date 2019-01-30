#pragma once

#include "Game.h"

class Physics {

public:
	struct Circle {
		int x, y;
		int r;
	};

	Physics();
	static double estimateAngle(SDL_Point point, Circle circle);
	static double estimateAngle(double angle);
	static double estimateBounceAngle(SDL_Rect rect, Circle circle);
	static double estimateVelocity (double strengh, Uint32 lastTime);

	static double estimateStrengh(double strengh, Uint32 lastTime);

	static double destTransform_x(int destRect_x, double velocity, int angle);
	static double destTransform_y(int destRect_y, double velocity, int angle);

private:
	static double Angle(int x1, int y1, int x2, int y2);
};