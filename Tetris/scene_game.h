#ifndef _SCENE_GAME_
#define _SCENE_GAME_

#include "scene.h"

class SceneGame : public Scene {
public:

	void load();
	void clean();
	void pause();
	void resume();
	void handleEvent(Uint32 dt);
	void update(Uint32 dt);
	void draw(SpriteRenderer *renderer);

	static SceneGame* Instance() {
		return &sceneGame;
	}

protected:
	SceneGame() { }

private:
	static SceneGame sceneGame;
};

#endif
