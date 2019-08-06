#include "scene_game.h"
#include "../engine/resource_manager.h"
#include <cstdlib>
#include <ctime>

SceneGame::SceneGame() : Scene()
{}

SceneGame::~SceneGame()
{
	clean();
}

void SceneGame::load()
{
	std::srand((int)std::time(nullptr));

	screenHeight = game->windowHeight;

	ResourceManager::loadTexture("./assets/textures/tile.bmp", "tile");
	ResourceManager::loadTexture("./assets/textures/tile_fall.bmp", "tile_fall");
	pieces = new Pieces();
	board = new Board(pieces, game->windowHeight);
	board->initBoard();
	counter = 0;

	// First piece
	currentPiece.kind = getRand(0, 6);
	currentPiece.rotation = getRand(0, 3);
	currentPiece.x = BOARD_WIDTH / 2 + pieces->getXInitialPosition(currentPiece.kind, currentPiece.rotation);
	currentPiece.y = pieces->getYInitialPosition(currentPiece.kind, currentPiece.rotation);
	//  Next piece
	nextPiece.kind = getRand(0, 6);
	nextPiece.rotation = getRand(0, 3);
	nextPiece.x = BOARD_WIDTH / 2 + pieces->getXInitialPosition(nextPiece.kind, nextPiece.rotation);
	nextPiece.y = -10;
}

void SceneGame::clean()
{
	delete board;
	delete pieces;
}

void SceneGame::pause()
{
}

void SceneGame::resume()
{
}

void SceneGame::handleEvent()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		game->isRunning = false;
		break;
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_RIGHT:
		{
			// Left move
			if (board->isPossibleMovement(currentPiece.x + 1, currentPiece.y, currentPiece.kind, currentPiece.rotation))
				currentPiece.x++;
			break;
		}
		case (SDLK_LEFT):
		{
			// Right move
			if (board->isPossibleMovement(currentPiece.x - 1, currentPiece.y, currentPiece.kind, currentPiece.rotation))
				currentPiece.x--;
			break;
		}
		case (SDLK_DOWN):
		{
			// Put down, check lines and game over
			while (board->isPossibleMovement(currentPiece.x, currentPiece.y + 1, currentPiece.kind, currentPiece.rotation))
			{
				currentPiece.y++;
			}
			board->storePiece(currentPiece.x, currentPiece.y, currentPiece.kind, currentPiece.rotation);
			board->deletePossibleLines();
			if (board->isGameOver())
			{
				exit(0);
			}
			// New piece if game continues
			createNewPiece();
			break;
		}
		case (SDLK_UP):
		{
			// Rotation
			if (board->isPossibleMovement(currentPiece.x, currentPiece.y + 1, currentPiece.kind, (currentPiece.rotation + 1) % 4))
				currentPiece.rotation = (currentPiece.rotation + 1) % 4;
			break;
		}
		break;
		}
	default:
		break;
	}
}

void SceneGame::update(unsigned int dt)
{
	counter += dt;
	if (counter >= SPEED)
	{
		if (board->isPossibleMovement(currentPiece.x, currentPiece.y + 1, currentPiece.kind, currentPiece.rotation))
		{
			currentPiece.y++;
		}
		else
		{
			board->storePiece(currentPiece.x, currentPiece.y, currentPiece.kind, currentPiece.rotation);
			board->deletePossibleLines();
			if (board->isGameOver())
			{
				exit(0);
			}
			// New piece if game continues
			createNewPiece();
		}
		counter = counter % SPEED;
	}
}

void SceneGame::draw(SpriteRenderer *sRenderer, GeometryRenderer *gRenderer)
{
	drawBoard(sRenderer, gRenderer);
	drawPiece(currentPiece, sRenderer);
	drawPiece(nextPiece, sRenderer);
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

void SceneGame::drawPiece(Piece piece, SpriteRenderer *renderer)
{
	int pixelsX = board->getXPosInPixels(piece.x);
	int pixelsY = board->getYPosInPixels(piece.y);
	for (int i = 0; i < PIECE_BLOCKS; i++)
	{
		for (int j = 0; j < PIECE_BLOCKS; j++)
		{
			if (pieces->getBlockType(piece.kind, piece.rotation, j, i) != 0)
				renderer->drawSprite(ResourceManager::getTexture("tile_fall"),
									 glm::vec2(pixelsX + i * BLOCK_SIZE, pixelsY + j * BLOCK_SIZE),
									 glm::vec2(25, 25), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		}
	}
}

void SceneGame::drawBoard(SpriteRenderer *sRenderer, GeometryRenderer *gRenderer)
{
	// Calculate the limits of the board in pixels
	int left = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2));
	int right = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));
	int height = screenHeight - (BLOCK_SIZE * BOARD_HEIGHT);

	// Rectangles that delimits the board
	glm::vec4 borderColor = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
	gRenderer->drawRect(glm::vec2(left - BOARD_LINE_WIDTH, height), glm::vec2(BOARD_LINE_WIDTH, BLOCK_SIZE * BOARD_HEIGHT), 0.0f, borderColor);
	gRenderer->drawRect(glm::vec2(right, height), glm::vec2(BOARD_LINE_WIDTH, BLOCK_SIZE * BOARD_HEIGHT), 0.0f, borderColor);

	// Drawing the blocks that are already stored in the board
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			// Check if the block is filled, if so, draw it
			if (!board->isFreeBlock(i, j))
				sRenderer->drawSprite(ResourceManager::getTexture("tile"),
									  glm::vec2(left + i * BLOCK_SIZE, height + j * BLOCK_SIZE),
									  glm::vec2(25, 25), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
		}
	}
}
