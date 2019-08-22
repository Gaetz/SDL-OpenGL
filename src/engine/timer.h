#ifndef TIMER_H
#define TIMER_H

#ifdef __linux__
	#include <SDL2/SDL.h>
#elif _WIN32
	#include <SDL.h>
#endif

// Hold time related functions.
// In charge of computing the delta time and
// ensure smooth game ticking.
class Timer
{
public:
    Timer();
    virtual ~Timer();

    // Compute delta time as the number of milliseconds since last frame
    unsigned int computeDeltaTime();

    // Wait if the game run faster than the decided FPS
    void delayTime();

private:
	const static int FPS = 60;
	const static int frameDelay = 1000 / FPS;

	// Time in milliseconds when frame starts
	unsigned int frameStart;

	// Last frame start time in milliseconds
	unsigned int lastFrame;

	// Time it tooks to run the loop. Used to cap framerate.
	unsigned int frameTime;
};

#endif