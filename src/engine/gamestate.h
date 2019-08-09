#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "renderer_sprite.h"
#include "renderer_geometry.h"
#include "game.h"

// Interface for scenes
class GameState {
public:
	virtual ~GameState() {}

	virtual void load() = 0;
	virtual void clean() = 0;
	
	virtual void handleEvent() = 0;
	virtual void update(uint dt) = 0;
	virtual void draw(SpriteRenderer *sRenderer, GeometryRenderer *gRenderer) = 0;

	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void setGame(Game *_game) = 0;
};

#endif