#include "game.hpp"
#include "sdl.hpp"
#include "tiles.hpp"
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>

void Game::run() {
	constexpr int WIN_W {800};
	constexpr int WIN_H {600};

	Sdl sdl("Dwarf", 800, 600);

	Tiles tiles(
		sdl, "../assets/ground4.bmp",
		{
			.num_rows = WIN_H / (128 / 4),
			.num_cols = WIN_W / 128,
			.num_layers = 4,
			// .num_rows = 2,
			// .num_cols = 2,
			// .num_layers = 2,
			.dstrect_size = 128,
			.srcrect_size = 32,
			.hitbox_size = 64,
			.y_offset = 128 / 4,
			.z_offset = 128 / 2
		}
	);

	bool is_running {true};

	while (is_running) {
		bool left_click {false};
		while (sdl.poll_event()) {
			if (sdl.has_event_type(SDL_KEYDOWN) &&
				sdl.has_keycode(SDLK_q)
			) {
				is_running = false;
			}
			if (sdl.has_event_type(SDL_MOUSEBUTTONDOWN) &&
				sdl.has_left_click()
			) {
				left_click = true;
			}
		}
		tiles.update(sdl.get_mouse_pos(), left_click);

		sdl.clear({30, 70, 70, 255});

		tiles.draw(sdl);

		sdl.present();
	}

}
