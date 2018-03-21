#ifndef _SCENE_GAME_
#define _SCENE_GAME_

#include "scene.h"
#include "piece.h"
#include "pieces.h"
#include "board.h"

class SceneGame : public Scene {
public:
	static SceneGame* Instance() {
		return &sceneGame;
	}
	void load();
	void clean();
	void pause();
	void resume();
	void handleEvent(Uint32 dt);
	void update(Uint32 dt);
	void draw(SpriteRenderer *sRenderer, GeometryRenderer *gRenderer);

	void createNewPiece();

	Piece currentPiece;

protected:
	SceneGame() { }

private:
	int getRand(int a, int b);

	Piece nextPiece;
	int screenHeight;
	Board *board;
	Pieces *pieces;

	void drawPiece(Piece piece, SpriteRenderer *renderer);
	void drawBoard(SpriteRenderer *renderer, GeometryRenderer *gRenderer);

	static SceneGame sceneGame;
};

#endif
