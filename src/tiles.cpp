#include "tiles.hpp"
#include "debug.hpp"
#include <SDL2/SDL_rect.h>

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
					dstrect, hitbox, srcrect
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

void Tiles::update() {
}

void Tiles::draw(const Sdl& sdl) const {
	for (const auto& tile : tiles) {
		SDL_Rect srcrect = tile.srcrect;
		SDL_Rect dstrect = tile.dstrect;
		sdl.copy(tex, &srcrect, &dstrect);
	}
}
