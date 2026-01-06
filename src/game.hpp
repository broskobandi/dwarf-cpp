#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <string>

class Game {
private:
	SDL_Window* win;
	SDL_Renderer* ren;
public:
	Game();
	~Game();
	Game(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(const Game&) = delete;
	Game& operator=(Game&&) = delete;
	void run();
};

#endif
