#include "game.hpp"
#include "debug.hpp"
#include <SDL2/SDL.h>
#include <stdexcept>
#include <string>

#define WIN_W 800
#define WIN_H 600

Game::Game() {
	if (SDL_Init(SDL_INIT_EVERYTHING))
		throw std::runtime_error("Failed to init SDL.");
	DBG("SDL initialized.");

	win = SDL_CreateWindow("Dwarf", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_W, WIN_H, SDL_WINDOW_SHOWN);
	if (!win) throw std::runtime_error("Failed to create window.");
	DBG("Window created.");

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);
	if (!ren) throw std::runtime_error("Failed to create renderer.");
	DBG("Renderer created.");
}

Game::~Game() {
	if (ren) {
		SDL_DestroyRenderer(ren);
		DBG("Renderer destroyed.");
	}
	if (win) {
		SDL_DestroyWindow(win);
		DBG("Window destroyed.");
	}
	SDL_Quit();
	DBG("SDL terminated.");
}

void Game::run() {
	SDL_Event event;
	bool is_running = true;

	if (SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND))
		throw std::runtime_error("Failed to set render draw blend mode.");
	DBG("Blendmode set.");

	while (is_running) {
		while (SDL_PollEvent(&event)) {
		}
		if (SDL_GetKeyboardState(nullptr)[SDL_SCANCODE_Q]) is_running = false;

		if (SDL_SetRenderDrawColor(ren, 30, 70, 70, 255))
			throw std::runtime_error("Failed to set render draw color.");
		if (SDL_RenderClear(ren))
			throw std::runtime_error("Failed to clear renderer.");

		SDL_RenderPresent(ren);
	}
}
