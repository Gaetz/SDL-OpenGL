#ifndef PIECE_H
#define PIECE_H

// Data for a Tetris piece
struct Piece {
	int x;
	int y;
	int kind;
	int rotation;
};

#endif