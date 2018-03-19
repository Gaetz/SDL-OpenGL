#include "scene_game.h"
#include "resource_manager.h"

SceneGame SceneGame::sceneGame;

void SceneGame::load()
{
	// Load textures
	ResourceManager::loadTexture("./assets/textures/tile.png", "tile");
}

void SceneGame::clean() {

}

void SceneGame::pause() {

}

void SceneGame::resume() {

}

void SceneGame::handleEvent(Uint32 dt) {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		game->isRunning = false;
		break;
	default:
		break;
	}
}


void SceneGame::update(Uint32 dt) {

}

void SceneGame::draw(SpriteRenderer * renderer)
{
	renderer->drawSprite(ResourceManager::getTexture("tile"),
		glm::vec2(200, 200), glm::vec2(25, 25), 45.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}
