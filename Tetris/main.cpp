#include "Game.h"

Game *game = nullptr;

int main(int argc, char **argv) {
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	// Time in milliseconds when frame starts
	Uint32 frameStart;

	// Last frame start time in milliseconds
	Uint32 lastFrame = 0;
	
	// Delta time
	Uint32 dt;

	// Time it tooks to run the loop. Used to cap framerate.
	int frameTime;

	game = new Game();
	game->init("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 450, 800, false);
	game->load();

	while (game->isRunning) {
		// Delta time
		frameStart = SDL_GetTicks();
		dt = frameStart - lastFrame;
		lastFrame = frameStart;

		// Game loop
		game->handleEvents(dt);
		game->update(dt);
		game->render();

		// Delay frame if game runs too fast
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < frameDelay) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	return 0;
}