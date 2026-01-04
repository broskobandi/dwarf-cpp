#include "sdl.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <stdexcept>
#include <SDL2/SDL.h>
#include "debug.hpp"

Sdl::Sdl(std::string title, int w, int h) {
	if (SDL_Init(SDL_INIT_EVERYTHING))
		throw std::runtime_error("Failed to init sdl.");
	DBG("SDL Initialized.");

	win = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		w, h,
		SDL_WINDOW_SHOWN
	);
	if (!win) throw std::runtime_error("Failed to create window.");
	DBG("Window created.");

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);
	if (!ren) throw std::runtime_error("Failed to create renderer.");
	DBG("Renderer created.");
}

Sdl::~Sdl() {
	if (ren) SDL_DestroyRenderer(ren);
	DBG("Renderer desrtoyed.");
	if (win) SDL_DestroyWindow(win);
	DBG("Window desrtoyed.");
	SDL_Quit();
	DBG("SDL terminated.");
}

bool Sdl::poll_event() {
	return (bool)SDL_PollEvent(&event);
}


bool Sdl::has_event_type(SDL_EventType type) const {
	return event.type == type;
}

bool Sdl::has_keycode(SDL_Keycode keycode) const {
	return event.key.keysym.sym == keycode;
}

void Sdl::clear() const {
	if (SDL_RenderClear(ren))
		throw std::runtime_error("Failed to clear renderer.");
}

void Sdl::clear(SDL_Color color) {
	if (SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a)) 
		throw std::runtime_error("Failed to set render draw color.");

	clear();
}

void Sdl::present() const {
	SDL_RenderPresent(ren);
}

SDL_Point Sdl::get_mouse_pos() const {
	SDL_Point pos {};
	SDL_GetMouseState(&pos.x, &pos.y);
	return pos;
}

bool Sdl::has_left_click() const {
	return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT);
}


SDL_Texture *Sdl::create_texture_from_bmp(std::string path) const {
	SDL_Surface *sur = SDL_LoadBMP(path.c_str());
	if (!sur) throw std::runtime_error("Failed to load bmp.");
	DBG("Bmp loaded.");

	SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, sur);
	if (!tex) {
		SDL_FreeSurface(sur);
		DBG("Surface freed.");
		throw std::runtime_error("Failed to create texture from surface.");
	}
	DBG("Texture created from surface.");

	SDL_FreeSurface(sur);
	DBG("Surface freed.");

	return tex;
}


void Sdl::copy(SDL_Texture* tex, SDL_Rect* srcrect, SDL_Rect* dstrect) const {
	if (SDL_RenderCopy(ren, tex, srcrect, dstrect))
		throw std::runtime_error("Failed to copy texture.");
}
