#ifndef GAMESTATE_MAIN_H
#define GAMESTATE_MAIN_H

#include "../engine/gamestate.h"
#include "piece.h"
#include "pieces.h"
#include "board.h"

#define SPEED 500

// Main scene of the game, contains all the game's logic
class GameStateMain : public GameState
{
public:
	GameStateMain();
	virtual ~GameStateMain();

	void load();
	void clean();
	void pause();
	void resume();
	void handleEvent(const InputState &);
	void update(unsigned int dt);
	void draw(SpriteRenderer *, GeometryRenderer *);
	void setGame(Game *);

	void createNewPiece();

	Piece currentPiece;

private:
	int getRand(int a, int b);

	int moveLeftKey;
	int moveRightKey;
	int rotateKey;
	int fallKey;

	Game *game;
	Pieces *pieces;
	Board *board;
	unsigned int counter;
	int screenHeight;

	Piece nextPiece;

	void drawPiece(Piece piece, SpriteRenderer *);
	void drawBoard(SpriteRenderer *, GeometryRenderer *);
};

#endif
