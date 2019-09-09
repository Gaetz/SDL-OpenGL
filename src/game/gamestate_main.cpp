#include "gamestate_main.h"
#include "../engine/resource_manager.h"

#include <cstdlib>
#include <ctime>

GameStateMain::GameStateMain(
		std::shared_ptr<SpriteRenderer> _sRenderer, 
		std::shared_ptr<GeometryRenderer> _gRenderer
	) : sRenderer(std::move(_sRenderer)), gRenderer(std::move(_gRenderer))
{
}

GameStateMain::~GameStateMain()
{
	clean();
}

void GameStateMain::setGame(Game *_game)
{
	game = _game;
}

void GameStateMain::load()
{
	std::srand((int)std::time(nullptr));

	screenHeight = game->windowHeight;
	moveLeftKey = SDL_SCANCODE_LEFT;
	moveRightKey = SDL_SCANCODE_RIGHT;
	rotateKey = SDL_SCANCODE_UP;
	fallKey = SDL_SCANCODE_DOWN;

	ResourceManager::loadTexture("./assets/textures/tile.png", "tile");
	ResourceManager::loadTexture("./assets/textures/tile_fall.png", "tile_fall");
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
	nextPiece.y = 20;
}

void GameStateMain::clean()
{
	delete board;
	delete pieces;
}

void GameStateMain::pause()
{
}

void GameStateMain::resume()
{
}

void GameStateMain::handleEvent(const InputState &inputState)
{
	// Right move
	if (inputState.keyboardState.isJustPressed(SDL_Scancode(moveRightKey)))
	{
		if (board->isPossibleMovement(currentPiece.x + 1, currentPiece.y, currentPiece.kind, currentPiece.rotation))
			currentPiece.x++;
	}
	// Left move
	if (inputState.keyboardState.isJustPressed(SDL_Scancode(moveLeftKey)))
	{
		if (board->isPossibleMovement(currentPiece.x - 1, currentPiece.y, currentPiece.kind, currentPiece.rotation))
			currentPiece.x--;
	}
	// Put down, check lines and game over
	if (inputState.keyboardState.isJustPressed(SDL_Scancode(fallKey)))
	{
		while (board->isPossibleMovement(currentPiece.x, currentPiece.y - 1, currentPiece.kind, currentPiece.rotation))
		{
			currentPiece.y--;
		}
		board->storePiece(currentPiece.x, currentPiece.y, currentPiece.kind, currentPiece.rotation);
		board->deletePossibleLines();
		if (board->isGameOver())
		{
			exit(0);
		}
		// New piece if game continues
		createNewPiece();
	}
	// Rotation
	if (inputState.keyboardState.isJustPressed(SDL_Scancode(rotateKey)))
	{
		if (board->isPossibleMovement(currentPiece.x, currentPiece.y - 1, currentPiece.kind, (currentPiece.rotation + 1) % 4))
			currentPiece.rotation = (currentPiece.rotation + 1) % 4;
	}
}

void GameStateMain::update(unsigned int dt)
{
	counter += dt;
	if (counter >= SPEED)
	{
		if (board->isPossibleMovement(currentPiece.x, currentPiece.y - 1, currentPiece.kind, currentPiece.rotation))
		{
			currentPiece.y--;
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

void GameStateMain::draw()
{
	drawBoard();
	drawPiece(currentPiece);
	drawPiece(nextPiece);
}

void GameStateMain::createNewPiece()
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

int GameStateMain::getRand(int a, int b)
{
	return std::rand() % (b - a + 1) + a;
}

void GameStateMain::drawPiece(Piece piece)
{
	int pixelsX = board->getXPosInPixels(piece.x);
	int pixelsY = board->getYPosInPixels(piece.y);
	for (int i = 0; i < PIECE_BLOCKS; i++)
	{
		for (int j = 0; j < PIECE_BLOCKS; j++)
		{
			if (pieces->getBlockType(piece.kind, piece.rotation, j, i) != 0)
			{
				sRenderer->drawSprite(ResourceManager::getTexture("tile_fall"),
									 Vector2(pixelsX + i * BLOCK_SIZE, pixelsY + j * BLOCK_SIZE),
									 Vector2(25, 25), 0.0f, Color(1.0f, 1.0f, 1.0f));
			}
		}
	}
}

void GameStateMain::drawBoard()
{
	// Calculate the limits of the board in pixels
	int left = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2));
	int right = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));
	int height = screenHeight - (BLOCK_SIZE * BOARD_HEIGHT);

	// Rectangles that delimits the board
	Color borderColor = Color(1.0f, 0.0f, 1.0f, 1.0f);
	gRenderer->drawRect(Vector2(left - BOARD_LINE_WIDTH, height), Vector2(BOARD_LINE_WIDTH, BLOCK_SIZE * BOARD_HEIGHT), 0.0f, borderColor);
	gRenderer->drawRect(Vector2(right, height), Vector2(BOARD_LINE_WIDTH, BLOCK_SIZE * BOARD_HEIGHT), 0.0f, borderColor);

	// Drawing the blocks that are already stored in the board
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			// Check if the block is filled, if so, draw it
			if (!board->isFreeBlock(i, j))
				sRenderer->drawSprite(ResourceManager::getTexture("tile"),
									  Vector2(left + i * BLOCK_SIZE, j * BLOCK_SIZE),
									  Vector2(25, 25), 0.0f, Color(1.0f, 1.0f, 1.0f));
		}
	}
}
