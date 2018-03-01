#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}


void Game::init(const char * title, int xPos, int yPos, int width, int height, bool isFullscreen)
{
	int flags = SDL_WINDOW_OPENGL;
	if (isFullscreen) {
		flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Subsystems initialised");
		
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		

		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);
		if (window) {
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Window initialised");
		}

		context = SDL_GL_CreateContext(window);
		if (context) {
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "OpenGL Context initialised");
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
	//SDL_RenderClear(renderer);



	//SDL_RenderPresent(renderer);
}


void Game::clean()
{
	SDL_DestroyWindow(window);
	//SDL_DestroyRenderer(renderer);
	SDL_Quit();
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Bye :)");
}
