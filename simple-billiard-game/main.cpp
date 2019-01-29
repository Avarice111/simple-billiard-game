/*
	_WIN64 version
*/

#include <SDL.h>

#undef main

#include <stdexcept>

#include <stdexcept>
#include <memory>
#include <string>
#include <set>
#include <tuple>
#include <iostream>
#include <cstdint>
#include <vector>
#include <array>
#include <math.h>

#define define M_PI  3.14159265358979323846 

struct Circle
{
	int x, y;
	int r;
};

auto errthrow = [](const std::string &e) {
	std::string errstr = e + " : " + SDL_GetError();
	SDL_Quit();
	throw std::runtime_error(errstr);
};

std::shared_ptr<SDL_Window> init_window(const int width = 320, const int height = 200) {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) errthrow("SDL_Init");

	SDL_Window *win = SDL_CreateWindow("SDL GAME",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, height, SDL_WINDOW_SHOWN);
	if (win == nullptr) errthrow("SDL_CreateWindow");
	std::shared_ptr<SDL_Window> window(win, [](SDL_Window * ptr) {
		SDL_DestroyWindow(ptr);
	});
	return window;
}

std::shared_ptr<SDL_Renderer> init_renderer(std::shared_ptr<SDL_Window> window) {
	SDL_Renderer *ren = SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) errthrow("SDL_CreateRenderer");
	std::shared_ptr<SDL_Renderer> renderer(ren, [](SDL_Renderer * ptr) {
		SDL_DestroyRenderer(ptr);
	});
	return renderer;
}

std::shared_ptr<SDL_Texture> load_texture(const std::shared_ptr<SDL_Renderer> renderer, const std::string fname)
{
	SDL_Surface *bmp = SDL_LoadBMP(fname.c_str());
	SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer.get(), bmp);
	std::shared_ptr<SDL_Texture> texture(tex, [](SDL_Texture *ptr) {
		SDL_DestroyTexture(ptr);
	});
	SDL_FreeSurface(bmp);
	return texture;
}

void render_billiard_table(std::shared_ptr<SDL_Renderer> renderer) {
	auto billiard_table = load_texture(renderer, "data/billiard_table.bmp");

	SDL_Rect Dstrect;

	Dstrect.x = 0;
	Dstrect.y = 167;
	Dstrect.w = 1024;
	Dstrect.h = 571;

	SDL_RenderCopy(renderer.get(), billiard_table.get(), NULL, &Dstrect);
}


using vec_t = std::array<double, 2>;


vec_t operator +(const vec_t &a, const vec_t &b) {

	return { a[0] + b[0], a[1] + b[1] };

}

vec_t operator -(const vec_t &a, const vec_t &b) {

	return { a[0] - b[0], a[1] - b[1] };

}

vec_t operator *(const vec_t &a, const vec_t &b) {

	return { a[0] * b[0], a[1] * b[1] };

}

vec_t operator *(const vec_t &a, const double &b) {

	return { a[0] * b, a[1] * b };

}

class billiard_table_t {
	public:
		vec_t position;
		vec_t size;


		void draw (std::shared_ptr<SDL_Renderer> renderer, const std::vector<int> collisions = {}) {

			auto billiard_table = load_texture(renderer, "data/billiard_table.bmp");

			SDL_Rect Dstrect;

			Dstrect.x = position[0];
			Dstrect.y = position[1];
			Dstrect.w = size[0];
			Dstrect.h = size[1];

			SDL_RenderCopy(renderer.get(), billiard_table.get(), NULL, &Dstrect);
		}
};


class stick_t {
public:

	vec_t position;
	vec_t size;
	double angle;
	double angleRad;
	double strengh;

	void draw(std::shared_ptr<SDL_Renderer> renderer) {

		auto billiard_table = load_texture(renderer, "data/stick.bmp");

		SDL_Rect Dstrect;

		Dstrect.x = position[0];
		Dstrect.y = position[1];
		Dstrect.w = size[0];
		Dstrect.h = size[1];
		SDL_Point point = { 0, 0 };

		SDL_RenderCopyEx(renderer.get(), billiard_table.get(), NULL, &Dstrect, angle, &point, SDL_FLIP_NONE);
	}


};

double distanceSquared(int x1, int y1, int x2, int y2)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX * deltaX + deltaY * deltaY;
}

class ball_t {
	public:

		vec_t position;
		vec_t size;
		vec_t velocity;

		void draw(std::shared_ptr<SDL_Renderer> renderer, std::string path) {

			auto billiard_table = load_texture(renderer, path);

			SDL_Rect Dstrect;

			Dstrect.x = position[0] - size[0] / 2;
			Dstrect.y = position[1] - size[1] / 2;
			Dstrect.w = size[0];
			Dstrect.h = size[1];

			SDL_RenderCopy(renderer.get(), billiard_table.get(), NULL, &Dstrect);

			
		}

		Circle mCollider;

		ball_t() {
			mCollider.r = size[0] / 2 - 1;
			mCollider.x = position[0];
			mCollider.y = position[1];
		}

		bool checkCollision(Circle& a, Circle& b) {
			int totalRadiusSquared = a.r + b.r;
			totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

			if (distanceSquared(a.x, a.y, b.x, b.y) < (totalRadiusSquared))
			{
				return true;
			}
			else 
			{
				return false;
			}
		}

		bool checkCollision(Circle& a, SDL_Rect& b) {
			int cX, cY;

			if (a.x < b.x)
			{
				cX = b.x;
			}
			else if (a.x > b.x + b.w)
			{
				cX = b.x + b.w;
			}
			else
			{
				cX = a.x;
			}

			if (a.y < b.y)
			{
				cY = b.y;
			}
			else if (a.y > b.y + b.h)
			{
				cY = b.y + b.h;
			}
			else
			{
				cY = a.y;
			}

			if (distanceSquared(a.x, a.y, cX, cY) < a.r * a.r)
			{
				return true;
			}
			else {
				return false;
			}
		}

		bool checkCollision(Circle& a, SDL_Point& b) {

		}

		/*void move(vec_t direction, stick_t stick) {
			velocity = { stick.strengh / 5, stick.strengh / 5 };
			position = position - velocity;
			velocity = velocity - vec_t{ 0.9, 0.9 };
		}*/

};

bool inRange(unsigned low, unsigned high, unsigned x)
{
	return  ((x - low) <= (high - low));
}

double distanceBeetweenPoints(vec_t a, vec_t b) {
	return sqrt(pow(b[0] - a[0], 2) + pow(b[1] - a[2], 2));
}

double angleVectors (vec_t &a, vec_t &b){
	 return atan2(b[1] - a[1], b[0] - a[0]) * (180 / M_PI);
}

double angleVectorsRad(vec_t &a, vec_t &b) {
	return atan2(b[1] - a[1], b[0] - a[0]);
}

vec_t setPosition(vec_t &a, double angle, double angleRad) {
	vec_t position;

	position = { a[0] + 50 * cos(angleRad) , a[1] + 50 * sin(angleRad)};

	return position;
}

vec_t setPosition(vec_t &a, double angle, double angleRad, double offset) {
	vec_t position;

	position = { a[0] + offset * cos(angleRad) , a[1] + offset * sin(angleRad) };

	return position;
}

enum gameStateEnum {
	aimBall,
	strenghStrike,
	ballInMove
};


int main() { // int argc, char **argv ) {	
	auto window = init_window(1024, 768);
	auto renderer = init_renderer(window);

	billiard_table_t billiard_table;
	ball_t white_ball;
	ball_t ball_one;
	stick_t stick;

	//table
	billiard_table.position = { 0, 0 };
	billiard_table.size = { 1024, 571 };

	//balls
	white_ball.position = { 744, 279 };
	white_ball.size = { 32, 32 };
	white_ball.velocity = { 0,0 };

	ball_one.position = { 200, 279 };
	ball_one.size = { 32, 32 };
	ball_one.velocity = { 0,0 };

	stick.position = { white_ball.position[0],
	white_ball.position[1]};
	stick.strengh = 0;

	SDL_Rect billiard_rect1 = { 86,0,398,52 };
	SDL_Rect billiard_rect2 = { 538,0,398,52 };
	SDL_Rect billiard_rect3 = { 0,86,52,394 };
	SDL_Rect billiard_rect4 = { 972,86,1024,394 };
	SDL_Rect billiard_rect5 = { 86,519,398,52 };
	SDL_Rect billiard_rect6 = { 538,519,398,52 };

	gameStateEnum gameState = aimBall;

	//game loop
	for (bool game_active = true; game_active; ) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) game_active = false;
			//stick
			switch (gameState) {
			case aimBall:
				if (event.type == SDL_MOUSEMOTION) {
					/*stick.position = {

					};*/
					stick.size = { 420, 12 };
					vec_t mouse_position = { (double)event.button.x, (double)event.button.y };
					stick.angle = angleVectors(white_ball.position, mouse_position);
					stick.angleRad = angleVectorsRad(white_ball.position, mouse_position);
					//std::cout << stick.angle << std::endl;
					//stick.position = vec_t{ (double)event.button.x, (double)event.button.y };
					stick.position = setPosition(white_ball.position, stick.angle, stick.angleRad);
					/*stick.position = white_ball.position + vec_t(isRange(10, 20, white_ball.position[0] - (double)event.button.x) ?
						white_ball.position[0] - (double)event.button.x : isRange(-10, -20, white_ball.position[0] - (double)event.button.x) ?
						-20*/

				}
				if (event.type == SDL_MOUSEBUTTONDOWN) {
					if (event.button.button == SDL_BUTTON_LEFT) {
						gameState = strenghStrike;
					}
				}
				break;
			case strenghStrike:
				/*if (event.type = SDL_MOUSEBUTTONUP) {
					if (event.button.button == SDL_BUTTON_LEFT) {
						std::cout << "button UP";
						gameState = ballInMove;
					}
				if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
					SDL_Log("Mouse Button 1 (left) is pressed.");
				}
				}*/
				if (event.type == SDL_MOUSEBUTTONDOWN) {
					if (event.button.button == SDL_BUTTON_LEFT) {
						gameState = ballInMove;
					}
				}
				break;
			case ballInMove:
				//SDL_Log("ballInMove");
				/*if (white_ball.velocity[0] == 0 && white_ball.velocity[1] == 0 && 
					ball_one.velocity[0] == 0 && ball_one.velocity[2] == 0) {*/
					//SAVE POINTS TODO
					//gameState = aimBall;
					//stick.strengh = 0;
				//}

				bool collided = white_ball.checkCollision(white_ball.mCollider, billiard_rect1);
				collided = white_ball.checkCollision(white_ball.mCollider, billiard_rect2);
				collided = white_ball.checkCollision(white_ball.mCollider, billiard_rect3);
				collided = white_ball.checkCollision(white_ball.mCollider, billiard_rect4);
				collided = white_ball.checkCollision(white_ball.mCollider, billiard_rect5);
				collided = white_ball.checkCollision(white_ball.mCollider, billiard_rect6);

				if (collided) {
					std::cout << "Kolizja!";
				}

				//white_ball.move(vec_t{ 20, 0 }, stick);
				break;

			}
		}
		//
		switch (gameState) {
		case strenghStrike:
			stick.strengh += 3.6;

			if (stick.strengh > 100)
				stick.strengh = 100;

			stick.position = setPosition(white_ball.position, stick.angle, stick.angleRad, 50 + stick.strengh);

			std::cout << stick.strengh << std::endl;
			break;
		case ballInMove:
			int hit = 0;
			
			hit <= 150 ? hit += 30 : hit = 140;
			stick.position = setPosition(white_ball.position, stick.angle, stick.angleRad, stick.strengh - hit);
		}

		SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
		SDL_RenderClear(renderer.get());
		//stick

		//draw
		billiard_table.draw(renderer);

		SDL_SetRenderDrawColor(renderer.get(), 255, 0, 0, 255);
		SDL_RenderDrawRect(renderer.get(), &billiard_rect1);
		SDL_RenderDrawRect(renderer.get(), &billiard_rect2);
		SDL_RenderDrawRect(renderer.get(), &billiard_rect3);
		SDL_RenderDrawRect(renderer.get(), &billiard_rect4);
		SDL_RenderDrawRect(renderer.get(), &billiard_rect5);
		SDL_RenderDrawRect(renderer.get(), &billiard_rect6);

		//promien 15
		white_ball.draw(renderer, "data/ball0.bmp");
		SDL_SetRenderDrawColor(renderer.get(), 255, 0, 0, 255);
		SDL_RenderDrawPoint(renderer.get(), white_ball.position[0], white_ball.position[1]);
		ball_one.draw(renderer, "data/ball1.bmp");

		switch (gameState) {
		case aimBall:
		case strenghStrike:
		case ballInMove:
			stick.draw(renderer);
			SDL_SetRenderDrawColor(renderer.get(), 0, 0, 0, 255);
			SDL_RenderDrawPoint(renderer.get(), stick.position[0], stick.position[1]);
			break;
		}
		/*SDL_SetRenderDrawColor(renderer.get(), 255, 255, 255, 255);
		SDL_RenderDrawLine(renderer.get(), white_ball.position[0], white_ball.position[1], NULL, NULL);*/

		SDL_RenderPresent(renderer.get());
		SDL_Delay(100);
	}

	return 0;
}