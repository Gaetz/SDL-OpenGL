#include "game.h"
#include "resource_manager.h"
#include <glm/gtc/matrix_transform.hpp>
#include "scene.h"
#include "../game/scene_game.h"

Game::Game() : isRunning(false),
			   windowWidth(0),
			   windowHeight(0)
{
}

Game::~Game()
{
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

	// Game scene
	changeScene(SceneGame::Instance());

}

void Game::handleEvents()
{
	scenes.back()->handleEvent();
}

void Game::update(unsigned int dt)
{
	scenes.back()->update(dt);
}

void Game::render()
{
	scenes.back()->draw(sRenderer, gRenderer);
}

void Game::clean()
{
	ResourceManager::clear();
}

void Game::changeScene(Scene *scene)
{
	// cleanup the current state
	if (!scenes.empty())
	{
		scenes.back()->clean();
		scenes.pop_back();
	}

	// store and load the new state
	scene->setGame(this);
	scenes.push_back(scene);
	scenes.back()->load();
}

void Game::pushScene(Scene *scene)
{
	// pause current state
	if (!scenes.empty())
	{
		scenes.back()->pause();
	}

	// store and init the new state
	scenes.push_back(scene);
	scenes.back()->load();
}

void Game::popScene()
{
	// cleanup the current state
	if (!scenes.empty())
	{
		scenes.back()->clean();
		scenes.pop_back();
	}

	// resume previous state
	if (!scenes.empty())
	{
		scenes.back()->resume();
	}
}
