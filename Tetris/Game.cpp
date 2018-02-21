#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}


void Game::init(const char * title, int xPos, int yPos, int width, int height, bool isFullscreen)
{
	int flags = 0;
	if (isFullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Subsystems initialised");
		
		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (window) {
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Window initialised");
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Renderer initialised");
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}
}


void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}


void Game::update()
{
}


void Game::render()
{
	SDL_RenderClear(renderer);



	SDL_RenderPresent(renderer);
}


void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Bye :)");
}
