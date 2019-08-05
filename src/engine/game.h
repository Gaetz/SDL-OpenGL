#ifndef GAME_H
#define GAME_H

#ifdef __linux__
	#include <SDL2/SDL.h>
#elif _WIN32
	#include <SDL.h>
#endif

#include <GL/glew.h>

#include "shader.h"
#include "renderer_sprite.h"
#include "renderer_geometry.h"
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
	int windowWidth, windowHeight;

private:
	SDL_Window *window;
	SDL_GLContext context;

	SpriteRenderer *sRenderer;
	GeometryRenderer *gRenderer;
	GameState state;
	std::vector<Scene*> scenes;
};

#endif