#include "game.h"
#include "resource_manager.h"
#include <glm/gtc/matrix_transform.hpp>
#include "gamestate.h"
#include "../game/gamestate_main.h"

Game::Game() : isRunning(false),
			   windowWidth(0),
			   windowHeight(0)
{
}

Game::~Game()
{
	cleanStates();
}

void Game::init(int screenWidth, int screenHeight)
{
	windowWidth = screenWidth;
	windowHeight = screenHeight;
	isRunning = true;
}

void Game::load()
{
	// Load shaders
	ResourceManager::loadShader("assets/shaders/sprite.vert", "assets/shaders/sprite.frag", nullptr, "sprite");
	ResourceManager::loadShader("assets/shaders/rect.vert", "assets/shaders/rect.frag", nullptr, "rect");
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(windowWidth), static_cast<GLfloat>(windowHeight), 0.0f, -1.0f, 1.0f);
	ResourceManager::getShader("sprite").use();
	ResourceManager::getShader("sprite").setInteger("image", 0);
	ResourceManager::getShader("sprite").setMatrix4("projection", projection);
	ResourceManager::getShader("rect").use();
	ResourceManager::getShader("rect").setMatrix4("projection", projection);
	// Set render-specific controls
	sRenderer = new SpriteRenderer(ResourceManager::getShader("sprite"));
	gRenderer = new GeometryRenderer(ResourceManager::getShader("rect"));

	// Game state
	changeState(new GameStateMain());
}

void Game::handleEvents()
{
	gameStates.back()->handleEvent();
}

void Game::update(unsigned int dt)
{
	gameStates.back()->update(dt);
}

void Game::render()
{
	gameStates.back()->draw(sRenderer, gRenderer);
}

void Game::clean()
{
	ResourceManager::clear();
}

void Game::changeState(GameState *state)
{
	// cleanup the current state
	if (!gameStates.empty())
	{
		gameStates.back()->clean();
		delete gameStates.back();
		gameStates.pop_back();
	}

	// store and load the new state
	state->setGame(this);
	gameStates.push_back(state);
	gameStates.back()->load();
}

void Game::pushState(GameState *state)
{
	// pause current state
	if (!gameStates.empty())
	{
		gameStates.back()->pause();
	}

	// store and init the new state
	gameStates.push_back(state);
	gameStates.back()->load();
}

void Game::popState()
{
	// cleanup the current state
	if (!gameStates.empty())
	{
		gameStates.back()->clean();
		delete gameStates.back();
		gameStates.pop_back();
	}

	// resume previous state
	if (!gameStates.empty())
	{
		gameStates.back()->resume();
	}
}

void Game::cleanStates()
{
	for (auto &it : gameStates)
	{
		delete it;
	}
}