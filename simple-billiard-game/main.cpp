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


		void draw (std::shared_ptr<SDL_Renderer> renderer) {

			auto billiard_table = load_texture(renderer, "data/billiard_table.bmp");

			SDL_Rect Dstrect;

			Dstrect.x = position[0];
			Dstrect.y = position[1];
			Dstrect.w = size[0];
			Dstrect.h = size[1];

			SDL_RenderCopy(renderer.get(), billiard_table.get(), NULL, &Dstrect);
		}
};

class ball_object_t {
	public:

		vec_t position;
		vec_t size;
		vec_t velocity;

		void draw(std::shared_ptr<SDL_Renderer> renderer) {

			auto billiard_table = load_texture(renderer, "data/ball0.bmp");

			SDL_Rect Dstrect;

			Dstrect.x = position[0] - size[0] / 2;
			Dstrect.y = position[1] - size[1] / 2;
			Dstrect.w = size[0];
			Dstrect.h = size[1];

			SDL_RenderCopy(renderer.get(), billiard_table.get(), NULL, &Dstrect);
		}
};


int main() { // int argc, char **argv ) {	
	auto window = init_window(1024, 768);
	auto renderer = init_renderer(window);

	billiard_table_t billiard_table;
	ball_object_t white_ball;

	//game loop
	for (bool game_active = true; game_active; ) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) game_active = false;
		}
		//
		SDL_RenderClear(renderer.get());

		//table
		billiard_table.position = { 0, 0 };
		billiard_table.size = { 1024, 571 };
		billiard_table.draw(renderer);

		//balls
		white_ball.position = { 744, 279 };
		white_ball.size = { 32, 32 };
		white_ball.draw(renderer);

		SDL_RenderPresent(renderer.get());
		SDL_Delay(100);
	}
	return 0;
}