#include "dwarf.hpp"
#include "debug.hpp"
#include <iostream>

Dwarf::Dwarf(const Sdl& sdl, std::string path_to_bmp, DwarfInitData&& id) :
	DwarfInitData(id),
	tex(sdl.create_texture_from_bmp(path_to_bmp)),
	srcrect({0, 0, srcrect_size, srcrect_size}),
	dstrect({starting_pos.x, starting_pos.y, dstrect_size, dstrect_size}),
	hitbox({dstrect.x, dstrect.y, hitbox_size, hitbox_size})
{}

Dwarf::~Dwarf() {
	if (tex) {
		DBG("Dwarf texture desrtoyed.");
	}
}

void Dwarf::update(Uint32 time, SDL_Point mouse_pos, bool left_click) {
	if (left_click) {
		has_target = true;
		target.x = mouse_pos.x;
		target.y = mouse_pos.y;
	}

	if (has_target) {
		is_moving = true;
		if (dstrect.x != target.x) {
			if (dstrect.x < target.x) {
				dstrect.x += pixels_per_frame;
				is_looking_left = false;
			}
			if (dstrect.x > target.x) {
				dstrect.x -= pixels_per_frame;
				is_looking_left = true;
			}
		}
		if (dstrect.y != target.y) {
			if (dstrect.y < target.y)
				dstrect.y += pixels_per_frame;
			if (dstrect.y > target.y)
				dstrect.y -= pixels_per_frame;
		}
		if (dstrect.x < target.x + pixels_per_frame &&
			dstrect.y < target.y + pixels_per_frame
		) {
			has_target = false;
			is_moving = false;
		}
	}

	if (is_moving) {
		if (time - time_of_last_img_update >= ticks_per_img) {
			if (cur_img + 1 < num_imgs) {
				cur_img++;
			} else {
				cur_img = 0;
			}
			time_of_last_img_update = time;
		}
		srcrect.x = cur_img * srcrect_size;
	} else {
		cur_img = 0;
	}
}

void Dwarf::draw(const Sdl& sdl) const {
	SDL_Rect srcrect = this->srcrect;
	SDL_Rect dstrect = this->dstrect;
	sdl.copy(tex, &srcrect, &dstrect, is_looking_left ? true : false);
}
