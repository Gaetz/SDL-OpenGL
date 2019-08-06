#ifndef SCENE_H
#define SCENE_H

#include "renderer_sprite.h"
#include "renderer_geometry.h"
#include "game.h"

class Scene {
public:
	virtual void load() = 0;
	virtual void clean() = 0;
	
	virtual void handleEvent() = 0;
	virtual void update(uint dt) = 0;
	virtual void draw(SpriteRenderer *sRenderer, GeometryRenderer *gRenderer) = 0;

	virtual void pause() = 0;
	virtual void resume() = 0;

	void setGame(Game *g) {
		game = g;
	}

protected:
	Scene() {}
	Game *game;
};

#endif