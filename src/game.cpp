#include "game.hpp"
#include "sdl.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>

void Game::run() {
	Sdl sdl("Dwarf", 800, 600);

	bool is_running {true};

	while (is_running) {
		while (sdl.poll_event()) {
			if (sdl.has_event_type(SDL_KEYDOWN) &&
				sdl.has_keycode(SDLK_q)
			) {
				is_running = false;
			}
		}
		sdl.clear({30, 70, 70, 255});
		sdl.present();
	}

}
