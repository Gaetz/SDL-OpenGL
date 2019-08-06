#include "engine/game.h"
#include "engine/window.h"
#include "engine/time.h"

int main( __attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{
	const char* title = "Tetris";
	const float SCREEN_WIDTH = 450;
	const float SCREEN_HEIGHT = 680;
	
	// Delta time
	int dt;

	Window window;
	if(!window.init(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false))
	{
		return 1;
	}
	
	Game game;
	game.init(SCREEN_WIDTH, SCREEN_HEIGHT);
	game.load();

	Time time;

	while (game.isRunning) {
		// Delta time
		dt = time.computeDeltaTime();
		window.updateFpsCounter(dt);

		// Game loop
		game.handleEvents();
		game.update(dt);

		window.clear();
		game.render();
		window.swapBuffer();

		// Delay frame if game runs too fast
		time.delayTime();
	}

	game.clean();
	window.clean();
	return 0;
}