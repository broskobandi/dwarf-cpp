#ifndef TILES_HPP
#define TILES_HPP

#include "sdl.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <vector>

struct TilesInitData {
	int num_rows;
	int num_cols;
	int num_layers;
	int dstrect_size;
	int srcrect_size;
	int hitbox_size;
	int y_offset;
	int z_offset;
};

class Tiles : private TilesInitData {
private:
	struct Tile {
		SDL_Rect dstrect;
		SDL_Rect hitbox;
		SDL_Rect srcrect;
		bool is_staggered;
		bool is_visible {true};
		bool is_highlighted {false};
		bool is_blocked_from_right {false};
		bool is_blocked_from_left {false};
		bool is_blocked_from_right_down {false};
		bool is_blocked_from_right_up {false};
		bool is_blocked_from_left_down {false};
		bool is_blocked_from_left_up {false};
		bool is_blocked_from_above {false};
		bool is_blocked_from_above_right_up {false};
		bool is_active {true};
		// bool test {false};
	};

	std::vector<Tile> tiles;
	int num_tiles_per_layer;
	int num_tiles;
	SDL_Texture *tex;
	SDL_Rect mouse_pointer {0, 0, 5, 5};

public:
	Tiles(const Tiles&) = delete;
	Tiles& operator=(const Tiles&) = delete;
	Tiles(Tiles&&) = delete;
	Tiles& operator=(Tiles&&) = delete;
	Tiles(const Sdl& sdl, std::string path_to_bmp, TilesInitData&& tile_init_data);
	~Tiles();
	// void update(SDL_Point mouse_pos, bool left_click);
	void update();
	void draw(const Sdl& sdl) const;
};

#endif
