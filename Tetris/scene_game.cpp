#include "scene_game.h"
#include "resource_manager.h"
#include <cstdlib>
#include <ctime>

SceneGame SceneGame::sceneGame;

void SceneGame::load()
{
	std::srand((Uint32)std::time(nullptr));
	ResourceManager::loadTexture("./assets/textures/tile.png", "tile");
	ResourceManager::loadTexture("./assets/textures/tile_fall.png", "tile_fall");
	/*
	// First piece
	currentPiece.kind = getRand(0, 6);
	currentPiece.rotation = getRand(0, 3);
	currentPiece.x = (BOARD_WIDTH / 2) + pieces->getXInitialPosition(currentPiece.kind, currentPiece.rotation);
	currentPiece.y = pieces->getYInitialPosition(currentPiece.kind, currentPiece.rotation);
	//  Next piece
	nextPiece.kind = getRand(0, 6);
	nextPiece.rotation = getRand(0, 3);
	nextPiece.x = BOARD_WIDTH + 5;
	nextPiece.y = 5;
	*/
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

void SceneGame::draw(SpriteRenderer *sRenderer, GeometryRenderer *gRenderer)
{
	gRenderer->drawRect(glm::vec2(0, 0), glm::vec2(50, 50), 0.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));


	sRenderer->drawSprite(ResourceManager::getTexture("tile"),
		glm::vec2(0, 0), glm::vec2(25, 25), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));


	sRenderer->drawSprite(ResourceManager::getTexture("tile_fall"),
		glm::vec2(25, 0), glm::vec2(25, 25), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));

}

void SceneGame::createNewPiece()
{
	// The new piece
	currentPiece.kind = nextPiece.kind;
	currentPiece.rotation = nextPiece.rotation;
	currentPiece.x = (BOARD_WIDTH / 2) + pieces->getXInitialPosition(currentPiece.kind, currentPiece.rotation);
	currentPiece.y = pieces->getYInitialPosition(currentPiece.kind, currentPiece.rotation);

	// Random next piece
	nextPiece.kind = getRand(0, 6);
	nextPiece.rotation = getRand(0, 3);
}

int SceneGame::getRand(int a, int b)
{
	return std::rand() % (b - a + 1) + a;
}

void SceneGame::drawPiece(Piece piece, SpriteRenderer * renderer)
{
	int pixelsX = board->getXPosInPixels(piece.x);
	int pixelsY = board->getYPosInPixels(piece.y);
	for (int i = 0; i < PIECE_BLOCKS; i++)
	{
		for (int j = 0; j < PIECE_BLOCKS; j++)
		{
			if (pieces->getBlockType(piece.kind, piece.rotation, j, i) != 0)
				renderer->drawSprite(ResourceManager::getTexture("tile"),
					glm::vec2(pixelsX + i * BLOCK_SIZE, pixelsY + j * BLOCK_SIZE),
					glm::vec2(25, 25), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		}
	}
}

void SceneGame::drawBoard(SpriteRenderer *renderer)
{
	/*
	// Calculate the limits of the board in pixels  
	int mX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
	int mX2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));
	int mY = screenHeight - (BLOCK_SIZE * BOARD_HEIGHT);

	// Check that the vertical margin is not to small
	//assert (mY > MIN_VERTICAL_MARGIN);

	// Rectangles that delimits the board
	mIO->DrawRectangle(mX1 - BOARD_LINE_WIDTH, mY, mX1, mScreenHeight - 1, BLUE);

	mIO->DrawRectangle(mX2, mY, mX2 + BOARD_LINE_WIDTH, mScreenHeight - 1, BLUE);

	// Check that the horizontal margin is not to small
	//assert (mX1 > MIN_HORIZONTAL_MARGIN);

	// Drawing the blocks that are already stored in the board
	mX1 += 1;
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			// Check if the block is filled, if so, draw it
			if (!mBoard->IsFreeBlock(i, j))
				mIO->DrawRectangle(mX1 + i * BLOCK_SIZE,
					mY + j * BLOCK_SIZE,
					(mX1 + i * BLOCK_SIZE) + BLOCK_SIZE - 1,
					(mY + j * BLOCK_SIZE) + BLOCK_SIZE - 1,
					RED);
		}
	}*/
}
