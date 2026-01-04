#ifndef SDL_HPP
#define SDL_HPP

#include <SDL2/SDL_blendmode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>
#include <string>

class Sdl {
private:
	SDL_Window* win;
	SDL_Renderer* ren;
	SDL_Event event;
public:
	Sdl(std::string title, int w, int h);
	Sdl(const Sdl&) = delete;
	Sdl(Sdl&&) = delete;
	Sdl& operator=(Sdl&&) = delete;
	Sdl& operator=(const Sdl&) = delete;
	~Sdl();
	bool poll_event();
	bool has_event_type(SDL_EventType type) const;
	bool has_keycode(SDL_Keycode keycode) const;
	void set_draw_color(SDL_Color color) const;
	void clear() const;
	void clear(SDL_Color color);
	void present() const;
	SDL_Point get_mouse_pos() const;
	bool has_left_click() const;
	SDL_Texture *create_texture_from_bmp(std::string path) const;
	void copy(SDL_Texture* tex, SDL_Rect* srcrect, SDL_Rect* dstrect) const;
	void fill_rect(SDL_Rect rect) const;
};

#endif
