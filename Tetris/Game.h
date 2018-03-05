#pragma once
#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#if defined(_WIN32) || defined(_WIN64)
#include <gl/glew.h>
#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#endif

#include "shader.h"

enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

class Game
{
public:
	Game();
	virtual ~Game();

	void init(const char* title, int xPos, int yPos, int width, int height, bool isFullscreen);
	void load();
	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }

private:
	bool isRunning;
	SDL_Window* window;
	SDL_GLContext context;

	GameState state;

};


#endif // !GAME_H
