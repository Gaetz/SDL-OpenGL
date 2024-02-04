#include <string>
#include <memory>


#include "engine/timer.h"
#include "engine/window.h"
#include "game/game.h"
#include "engine.h"

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

    Engine engine(std::make_unique<Game>(), title, SCREEN_WIDTH, SCREEN_HEIGHT);
    engine.start();
    engine.run();
    engine.shutdown();
	return 0;
}
