#include "board.h"

Board::Board(Pieces *pieces, int screenHeight) : pieces(pieces), screenHeight(screenHeight)
{
}

void Board::initBoard()
{
	for (int i = 0; i < BOARD_WIDTH; i++)
		for (int j = 0; j < BOARD_HEIGHT; j++)
			board[i][j] = POS_FREE;
}

void Board::deleteLine(int y)
{
	for (int j = y; j < BOARD_HEIGHT - 1; j++)
	{
		for (int i = 0; i < BOARD_WIDTH; i++)
		{
			board[i][j] = board[i][j + 1];
		}
	}
}

int Board::getXPosInPixels(int pos)
{
	return BOARD_POSITION - BLOCK_SIZE * (BOARD_WIDTH / 2) + pos * BLOCK_SIZE;
}

int Board::getYPosInPixels(int pos)
{
	return pos * BLOCK_SIZE;
}

bool Board::isFreeBlock(int x, int y)
{
	if (board[x][y] == POS_FREE)
		return true;
	else
		return false;
}

bool Board::isPossibleMovement(int x, int y, int piece, int rotation)
{
	// Checks collision with pieces already stored in the board or the board limits
	// ii and j1 are the ingame block coordinates, i2 and j2 the local block coordinates
	for (int i1 = x, i2 = 0; i1 < x + PIECE_BLOCKS; i1++, i2++)
	{
		for (int j1 = y, j2 = 0; j1 < y + PIECE_BLOCKS; j1++, j2++)
		{
			// Check if the piece is outside the limits of the board
			if (i1 < 0 ||
				i1 > BOARD_WIDTH - 1 ||
				j1 < 0)
			{
				if (pieces->getBlockType(piece, rotation, j2, i2) != 0)
					return false;
			}
			// Check if the piece have collisioned with a block already stored in the map
			if (j1 < BOARD_HEIGHT - 1)
			{
				if (pieces->getBlockType(piece, rotation, j2, i2) != 0 && !isFreeBlock(i1, j1))
					return false;
			}
		}
	}
	// No collision
	return true;
}

void Board::storePiece(int x, int y, int piece, int rotation)
{
	for (int i1 = x, i2 = 0; i1 < x + PIECE_BLOCKS; i1++, i2++)
	{
		for (int j1 = y, j2 = 0; j1 < y + PIECE_BLOCKS; j1++, j2++)
		{
			// Store only the blocks of the piece that are not holes
			if (pieces->getBlockType(piece, rotation, j2, i2) != 0)
				board[i1][j1] = POS_FILLED;
		}
	}
}

void Board::deletePossibleLines()
{
	for (int j = BOARD_HEIGHT - 1; j >= 0 ; j--)
	{
		int i = 0;
		while (i < BOARD_WIDTH)
		{
			if (board[i][j] != POS_FILLED)
				break;
			i++;
		}
		if (i >= BOARD_WIDTH)
			deleteLine(j);
	}
}

bool Board::isGameOver()
{
	//If the first line has blocks, then, game over
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		if (board[i][BOARD_HEIGHT - 1] == POS_FILLED)
			return true;
	}
	return false;
}
