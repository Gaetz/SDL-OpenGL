#ifndef GAME_H
#define GAME_H

#ifdef __linux__
	#include <SDL2/SDL.h>
#elif _WIN32
	#include <SDL.h>
#endif

#include <GL/glew.h>

#include "input_manager.h"
#include "shader.h"
#include "renderer_sprite.h"
#include "renderer_geometry.h"
#include <vector>

class GameState;

// This game class manages game states and triggers their logic.
// It supports gamestate stacking. It does not implement a 
// gameobject/entity/whatever logic to let you free to choose
// your architecture.
class Game
{
public:
	Game();
	virtual ~Game();

	void init(int screenWidth, int screenHeight);
	void load();
	void handleInputs();
	void update(unsigned int dt);
	void render();
	void clean();

	void changeState(GameState *);
	void pushState(GameState *);
	void popState();
	void cleanStates();

	bool isRunning;
	int windowWidth, windowHeight;

private:
	InputManager *inputManager;
	SpriteRenderer *sRenderer;
	GeometryRenderer *gRenderer;
	std::vector<GameState*> gameStates;
};

#endif