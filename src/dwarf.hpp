#ifndef DWARF_HPP
#define DWARF_HPP

#include "sdl.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_stdinc.h>
#include <string>

struct DwarfInitData {
	SDL_Point starting_pos;
	int dstrect_size;
	int srcrect_size;
	int hitbox_size;
	int pixels_per_frame;
	Uint32 ticks_per_img;
	int num_imgs;
};

class Dwarf : private DwarfInitData {
private:
	SDL_Texture* tex;
	SDL_Rect srcrect;
	SDL_Rect dstrect;
	SDL_Rect hitbox;
	int cur_img {0};
	Uint32 time_of_last_img_update {0};
	SDL_Point target {};
	bool is_moving {false};
	bool has_target {false};
	bool is_looking_left {false};
public:
	Dwarf(const Sdl& sdl, std::string path_to_bmp, DwarfInitData&& init_data);
	Dwarf(const Dwarf&) = delete;
	Dwarf(Dwarf&&) = delete;
	Dwarf& operator=(const Dwarf&) = delete;
	Dwarf& operator=(Dwarf&&) = delete;
	~Dwarf();
	void update(Uint32 time, SDL_Point mouse_pos, bool left_click);
	void draw(const Sdl& sdl) const;
};

#endif
