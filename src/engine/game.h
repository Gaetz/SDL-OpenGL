#ifndef GAME_H
#define GAME_H

#ifdef __linux__
	#include <SDL2/SDL.h>
#elif _WIN32
	#include <SDL.h>
#endif

#include <GL/glew.h>
#include <vector>
#include <memory>

#include "input_manager.h"
#include "shader.h"
#include "renderer_sprite.h"
#include "renderer_geometry.h"

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

	void changeState(std::unique_ptr<GameState>);
	void pushState(std::unique_ptr<GameState>);
	void popState();

	bool isRunning;
	int windowWidth, windowHeight;

private:
	std::unique_ptr<InputManager> inputManager;
	std::shared_ptr<SpriteRenderer> sRenderer;
	std::shared_ptr<GeometryRenderer> gRenderer;
	std::vector<std::unique_ptr<GameState>> gameStates;
};

#endif