#include "timer.h"

Timer::Timer() : frameStart(0), lastFrame(0), frameTime(0)
{
}

Timer::~Timer()
{
}

unsigned int Timer::computeDeltaTime()
{
    frameStart = SDL_GetTicks();
    unsigned int dt = frameStart - lastFrame;
    lastFrame = frameStart;
    return dt;
}

void Timer::delayTime()
{
    frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < frameDelay) {
        SDL_Delay(frameDelay - frameTime);
    }
}

