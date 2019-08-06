#ifndef BOARD_H
#define BOARD_H

#include "pieces.h"

#define BOARD_LINE_WIDTH 6          // Width of each of the two lines that delimit the board
#define BLOCK_SIZE 25               // Width and Height of each block of a piece
#define BOARD_POSITION 225	        // Center position of the board from the left of the screen
#define BOARD_WIDTH 10              // Board width in blocks 
#define BOARD_HEIGHT 20             // Board height in blocks
#define MIN_VERTICAL_MARGIN 25      // Minimum vertical margin for the board limit      
#define MIN_HORIZONTAL_MARGIN 25    // Minimum horizontal margin for the board limit
#define PIECE_BLOCKS 5              // Number of horizontal and vertical blocks of a matrix piece

// Tetris board. Know if their is a block or no
// at a specific position. Provides utils functions
// to help running the game.
class Board
{
public:
	Board(Pieces *pieces, int screenHeight);

	// Get horizontal coordinate in pixel from a horizontal coordinate in blocks
	int getXPosInPixels(int pos);

	// Get vertical coordinate in pixel from a vertical coordinate in blocks
	int getYPosInPixels(int pos);

	// Check if block at coordinates is free
	bool isFreeBlock(int x, int y);

	// Check if piece with given rotation can move
	bool isPossibleMovement(int x, int y, int piece, int rotation);

	// Store piece in the board by filling blocks
	void storePiece(int x, int y, int piece, int rotation);

	// Check which lines should be deleted and delete them
	void deletePossibleLines();

	// Check if game is over
	bool isGameOver();
	
	// Init board with empty positions
	void initBoard();

private:

	// POS_FREE = free position of the board; POS_FILLED = filled position of the board
	enum { POS_FREE, POS_FILLED };

	// Board that contains the pieces
	int board[BOARD_WIDTH][BOARD_HEIGHT]; 

	// Pieces tool
	Pieces *pieces;

	// Screen height
	int screenHeight;

	// Delete y line and but all line above one line down
	void deleteLine(int y);
};

#endif
