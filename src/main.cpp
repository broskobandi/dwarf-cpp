#include <iostream>
#include <stdexcept>
#define SDL_MAIN_HANDLED
#include "game.hpp"

int main(void) {
	try {
		Game game;
		game.run();
	} catch (const std::runtime_error& e) {
		std::cerr << e.what() << "\n";
	}

	return 0;
}
