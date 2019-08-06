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

class Scene;

class Game
{
public:
	Game();
	virtual ~Game();

	void init(int screenWidth, int screenHeight);
	void load();
	void handleEvents();
	void update(unsigned int dt);
	void render();
	void clean();

	void changeScene(Scene *scene);
	void pushScene(Scene *scene);
	void popScene();
	void cleanScenes();

	bool isRunning;
	int windowWidth, windowHeight;

private:
	SpriteRenderer *sRenderer;
	GeometryRenderer *gRenderer;
	std::vector<Scene*> scenes;
};

#endif