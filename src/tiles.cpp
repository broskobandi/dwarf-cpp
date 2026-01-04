#include "tiles.hpp"
#include "debug.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <cstddef>
#include <iostream>

using std::size_t;

Tiles::Tiles(const Sdl& sdl, std::string path_to_bmp, TilesInitData&& id) :
	TilesInitData(id),
	num_tiles_per_layer(id.num_cols * id.num_rows),
	num_tiles(num_tiles_per_layer * id.num_layers),
	tex(sdl.create_texture_from_bmp(path_to_bmp))
{
	for (int z = 0; z < num_layers; z++) {
		for (int y = 0; y < num_rows; y++) {
			int x_offset = y % 2 == 0 ? 0 : dstrect_size / 2;
			for (int x = 0; x < num_cols; x++) {
				SDL_Rect dstrect {
					x * dstrect_size + x_offset,
					y * y_offset - z * z_offset,
					dstrect_size,
					dstrect_size
				};
				SDL_Rect hitbox {
					dstrect.x + (dstrect_size - hitbox_size) / 2,
					dstrect.y,
					hitbox_size,
					hitbox_size
				};
				SDL_Rect srcrect {
					0, 0, srcrect_size, srcrect_size
				};
				tiles.push_back({
					dstrect, hitbox, srcrect, x_offset ? true : false
				});
			}
		}
	}
}

Tiles::~Tiles() {
	if (tex) {
		SDL_DestroyTexture(tex);
		DBG("Texture desrtoyed.");
	}
}

void Tiles::update(SDL_Point mouse_pos, bool left_click) {
	int i = 0;
	for (auto& tile : tiles) {

		// Calculate indicies of important tiles

		size_t tile_above_index =
			static_cast<size_t>(i + num_tiles_per_layer);
		size_t tile_right_down_index =
			static_cast<size_t>(i + num_cols +
			(tile.is_staggered ? 1 : 0));
		size_t tile_left_down_index =
			static_cast<size_t>(i + num_cols -
			(tile.is_staggered ? 0 : 1));
		size_t tile_right_up_index =
			static_cast<size_t>(i - num_cols +
			(tile.is_staggered ? 1 : 0));
		size_t tile_left_up_index =
			static_cast<size_t>(i - num_cols -
			(tile.is_staggered ? 0 : 1));
		size_t tile_above_right_up_index =
			tile_above_index - static_cast<size_t>(num_cols) +
			(tile.is_staggered ? 1 : 0);

		// Find blocking tiles
		
		if (tile_above_index < tiles.size() &&
			tiles.at(tile_above_index).dstrect.x == tile.dstrect.x &&
			tiles.at(tile_above_index).is_visible
		) {
			tile.is_blocked_from_above = true;
		} else {
			tile.is_blocked_from_above = false;
		}

		if (tile_left_down_index < tiles.size() &&
			tiles.at(tile_left_down_index).dstrect.y ==
				tile.dstrect.y + y_offset &&
			tiles.at(tile_left_down_index).is_visible
		) {
			tile.is_blocked_from_left_down = true;
		} else {
			tile.is_blocked_from_left_down = false;
		}

		if (tile_right_down_index < tiles.size() &&
			tiles.at(tile_right_down_index).dstrect.y ==
				tile.dstrect.y + y_offset &&
			tiles.at(tile_right_down_index).is_visible
		) {
			tile.is_blocked_from_right_down = true;
		} else {
			tile.is_blocked_from_right_down = false;
		}

		if (tile_left_up_index < tiles.size() &&
			tiles.at(tile_left_up_index).dstrect.y ==
				tile.dstrect.y - y_offset &&
			tiles.at(tile_left_up_index).is_visible
		) {
			tile.is_blocked_from_left_up = true;
		} else {
			tile.is_blocked_from_left_up = false;
		}

		if (tile_right_up_index < tiles.size() &&
			tiles.at(tile_right_up_index).dstrect.y ==
				tile.dstrect.y - y_offset &&
			tiles.at(tile_right_up_index).is_visible
		) {
			tile.is_blocked_from_right_up = true;
		} else {
			tile.is_blocked_from_right_up = false;
		}

		// Set activity

		if (!tile.is_blocked_from_above && 
			tile.is_highlighted &&
			left_click
		) {
			tile.is_active = false;
		}

		// Set visibility

		if ((!tile.is_blocked_from_above ||
			!tile.is_blocked_from_right_down ||
			!tile.is_blocked_from_left_down) &&
			tile.is_active
		) {
			tile.is_visible = true;
		} else {
			tile.is_visible = false;
		}

		// Set highlight

		if (!tile.is_blocked_from_above &&
			mouse_pos.x >= tile.hitbox.x &&
			mouse_pos.x <= tile.hitbox.x + hitbox_size &&
			mouse_pos.y >= tile.hitbox.y &&
			mouse_pos.y <= tile.hitbox.y + hitbox_size
		) {
			tile.is_highlighted = true;
		} else {
			tile.is_highlighted = false;
		}

		// Test indicies

		// if (tile_right_down_index < tiles.size() &&
		// 	tiles.at(tile_right_down_index).dstrect.y ==
		// 		tile.dstrect.y + y_offset &&
		// 	tile.is_highlighted 
		// ) {
		// 	tiles.at(tile_right_down_index).test = true;
		// }

		// if (tile_left_down_index < tiles.size() &&
		// 	tiles.at(tile_left_down_index).dstrect.y ==
		// 		tile.dstrect.y + y_offset &&
		// 	tile.is_highlighted 
		// ) {
		// 	tiles.at(tile_left_down_index).test = true;
		// }
		
		// if (tile_right_up_index < tiles.size() &&
		// 	tiles.at(tile_right_up_index).dstrect.y ==
		// 		tile.dstrect.y - y_offset &&
		// 	tile.is_highlighted 
		// ) {
		// 	tiles.at(tile_right_up_index).test = true;
		// }

		// if (tile_left_up_index < tiles.size() &&
		// 	tiles.at(tile_left_up_index).dstrect.y ==
		// 		tile.dstrect.y - y_offset &&
		// 	tile.is_highlighted 
		// ) {
		// 	tiles.at(tile_left_up_index).test = true;
		// }

		// if (tile_above_right_up_index < tiles.size() &&
		// 	tiles.at(tile_above_right_up_index).dstrect.y ==
		// 		tile.dstrect.y - y_offset - z_offset &&
		// 	tile.is_highlighted 
		// ) {
		// 	tiles.at(tile_above_right_up_index).test = true;
		// }

		i++;
	}
}

void Tiles::draw(const Sdl& sdl) const {
	// int num = 0;
	for (const auto& tile : tiles) {
		if (!tile.is_visible) continue;
		// if (tile.is_blocked_from_above &&
		// 	tile.is_blocked_from_left_down &&
		// 	tile.is_blocked_from_left_down
		// ) continue;
		if (tile.is_highlighted) {
			SDL_SetTextureAlphaMod(tex, 128);
		} else {
			SDL_SetTextureAlphaMod(tex, 255);
		}
		SDL_Rect srcrect = tile.srcrect;
		SDL_Rect dstrect = tile.dstrect;
		sdl.copy(tex, &srcrect, &dstrect);
		// num++;
	}
	// std::cout << num << "\n";
	// for (const auto& tile : tiles) {
	// 	if (tile.test) {
	// 		sdl.set_draw_color({255, 0, 0, 128});
	// 		sdl.fill_rect(tile.hitbox);
	// 	}
	// }
}
