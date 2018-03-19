#ifndef _SCENE_
#define _SCENE_

#include "sprite_renderer.h"
#include "game.h"

class Scene {
public:
	virtual void load() = 0;
	virtual void clean() = 0;
	
	virtual void handleEvent(Uint32 dt) = 0;
	virtual void update(Uint32 dt) = 0;
	virtual void draw(SpriteRenderer *renderer) = 0;

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