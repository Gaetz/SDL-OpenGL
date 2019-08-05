#ifndef TIME_H
#define TIME_H

#ifdef __linux__
	#include <SDL2/SDL.h>
#elif _WIN32
	#include <SDL.h>
#endif

class Time
{
public:
    Time();
    virtual ~Time();

    // Compute delta time as the number of milliseconds since last frame
    int computeDeltaTime();

    // Wait if the game run faster than the decided FPS
    void delayTime();

private:
	const static int FPS = 60;
	const static int frameDelay = 1000 / FPS;

	// Time in milliseconds when frame starts
	int frameStart;

	// Last frame start time in milliseconds
	int lastFrame;

	// Time it tooks to run the loop. Used to cap framerate.
	int frameTime;
};

#endif