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
#include "sprite_renderer.h"
#include <vector>


#define WAIT_TIME 700   

enum GameState {
	GAME_PLAY,
	GAME_MENU,
	GAME_WIN
};

class Scene;

class Game
{
public:
	Game();
	virtual ~Game();

	void init(const char* title, int xPos, int yPos, int width, int height, bool isFullscreen);
	void load();
	void handleEvents(Uint32 dt);
	void update(Uint32 dt);
	void render();
	void clean();

	void changeScene(Scene *scene);
	void pushScene(Scene *scene);
	void popScene();

	bool isRunning;

private:
	SDL_Window *window;
	SDL_GLContext context;
	int windowWidth, windowHeight;

	SpriteRenderer *renderer;
	GameState state;
	std::vector<Scene*> scenes;
};


#endif // !GAME_H
