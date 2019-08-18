#include <string>
#include <memory>

#include "engine/log.h"
#include "engine/game.h"
#include "engine/window.h"
#include "engine/time.h"

LogConfig LOG_CONFIG = {};

int main( __attribute__((unused)) int argc, __attribute__((unused)) char **argv)
{
	const std::string title = "Tetris";
	const float SCREEN_WIDTH = 450;
	const float SCREEN_HEIGHT = 680;
	
    // Init logging
    LOG_CONFIG.reporting_level = Debug;
    LOG_CONFIG.restart = true;
    if (LOG_CONFIG.restart)
    {
        Log::restart();
    }

	// Delta time
	int dt;

	// Main game elements loading
	auto window(IWindow::create(title));
	if(!window->init(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false))
	{
		return 1;
	}
	window->logGlParams();
	
	Game game;
	game.init(SCREEN_WIDTH, SCREEN_HEIGHT);
	game.load();

	Time time;

	// Game loop
	while (game.isRunning) {
		dt = time.computeDeltaTime();
		window->updateFpsCounter(dt);

		game.handleInputs();
		game.update(dt);

		window->clear();
		game.render();
		window->swapBuffer();

		// Delay frame if game runs too fast
		time.delayTime();
	}

	// Exit game
	game.clean();
	window->clean();
	return 0;
}