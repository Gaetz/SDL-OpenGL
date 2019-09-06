#include <string>
#include <memory>


#include "engine/timer.h"
#include "engine/window.h"
#include "engine/game.h"

LogConfig LOG_CONFIG = {};

// Use Graphics Card
#define DWORD unsigned int
#if defined(WIN32) || defined(_WIN32)
extern "C" { __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001; }
extern "C" { __declspec(dllexport) DWORD AmdPowerXpressRequestHighPerformance = 0x00000001; }
#else 
extern "C" { int NvOptimusEnablement = 1; }
extern "C" { int AmdPowerXpressRequestHighPerformance = 1; }
#endif

int main(int argc, char *argv[])
{
	const std::string title = "Tetris";
	const int SCREEN_WIDTH = 450;
	const int SCREEN_HEIGHT = 680;
	
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

	Timer timer;

	// Game loop
	while (game.isRunning) {
		dt = timer.computeDeltaTime();
		window->updateFpsCounter(dt);

		game.handleInputs();
		game.update(dt);

		window->clear();
		game.render();
		window->swapBuffer();

		// Delay frame if game runs too fast
		timer.delayTime();
	}

	// Exit game
	game.clean();
	window->clean();
	return 0;
}
