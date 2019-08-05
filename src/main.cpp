#include "engine/game.h"
#include "engine/window.h"

int main( __attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	const float SCREEN_WIDTH = 450;
	const float SCREEN_HEIGHT = 800;

	// Time in milliseconds when frame starts
	int frameStart;

	// Last frame start time in milliseconds
	int lastFrame = 0;
	
	// Delta time
	long dt;

	// Time it tooks to run the loop. Used to cap framerate.
	int frameTime;

	Window window;
	if(!window.init("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false))
	{
		return 1;
	}
	
	Game game;
	game.init(SCREEN_WIDTH, SCREEN_HEIGHT);
	game.load();

	while (game.isRunning) {
		// Delta time
		frameStart = SDL_GetTicks();
		dt = frameStart - lastFrame;
		lastFrame = frameStart;
		window.updateFpsCounter(dt);

		// Game loop
		game.handleEvents(dt);
		game.update(dt);

		window.clear();
		game.render();
		window.swapBuffer();

		// Delay frame if game runs too fast
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < frameDelay) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game.clean();
	window.clean();
	return 0;
}