#include "pieces.h"

Pieces::Pieces()
{
}

int Pieces::getBlockType(int piece, int rotation, int x, int y)
{
	return pieces[piece][rotation][x][y];
}

int Pieces::getXInitialPosition(int piece, int rotation)
{
	return piecesInitialPosition[piece][rotation][0];
}

int Pieces::getYInitialPosition(int piece, int rotation)
{
	return piecesInitialPosition[piece][rotation][1];
}
