#include "../include/Physics.h"


Physics::Physics() {

}

double Physics::Angle(int x1, int y1, int x2, int y2) {
	return atan2(y2 - y1, x2 - x1) * (180 / M_PI);
}

double Physics::estimateAngle(SDL_Point point, Circle circle) {
	double angle = Physics::Angle(point.x, point.y, circle.x, circle.y);

	return -angle;
}

double Physics::estimateAngle(double angle) {
	double new_angle;
	if (angle < 0) {
		new_angle = 180 - abs(angle);
	}
	else {
		new_angle = angle - 180;
	}
	return new_angle;
}

double Physics::estimateBounceAngle(SDL_Rect rect, Circle circle) {
	double angle = Angle(rect.x, rect.y, circle.x, circle.y);
	double new_angle;

	if (angle <= 0) {
		new_angle = 180 - 2 * (180 + angle);
		std::cout << angle << std::endl;
	}
	else {
		new_angle = 180 - 2 * (180 - angle);
		std::cout << angle << std::endl;
	}

	return new_angle;
}

double Physics::estimateVelocity(double strengh, Uint32 lastTime ) {
	double velocity = strengh * lastTime / Game::DELAY_TIME;

	return velocity;
}

double Physics::estimateStrengh(double strengh, Uint32 lastTime) {
	strengh += 3 * lastTime / Game::DELAY_TIME;

	return strengh;
}

double Physics::destTransform_x(int destRect_x, double velocity, int angle) {
	if (angle >= 90) {
		return destRect_x - velocity * (angle - 90) / 90;
	}
	else if (angle >= 0) {
		return destRect_x + velocity * (90 - angle) / 90;
	}
	else if (angle < -90) {
		return destRect_x - velocity * abs(angle + 90)  / 90;
	}
	else {
		return destRect_x + velocity * (90 + angle) / 90;
	}
}

double Physics::destTransform_y(int destRect_y, double velocity, int angle) {
	if (angle > 90) {
		return destRect_y + velocity * (180 - angle) / 90;
	}
	else if (angle >= 0) {
		return destRect_y + velocity * angle / 90;
	}
	else if (angle < -90) {
		return destRect_y - velocity * (180 - abs(angle)) / 90;
	}
	else {
		return destRect_y + velocity * angle / 90;
	}
}
