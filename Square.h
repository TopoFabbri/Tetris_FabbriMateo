#pragma once

#include "Globals.h"

struct Square
{
private:
	COORDS upLeft = initPiecePos;
	COORDS upRight{ upLeft.x + 1, upLeft.y };
	COORDS lowLeft{ upLeft.x, upLeft.y + 1 };
	COORDS lowRight{ upLeft.x + 1, upLeft.y + 1 };
	COLORS color = BlackOnYellow;
	ROT rot = ROT::Up;

	bool DownCollideCell(CELL board[maxX][maxY], COORDS cell);
	bool LeftCollideCell(CELL board[maxX][maxY], COORDS cell);
	bool RightCollideCell(CELL board[maxX][maxY], COORDS cell);

public:
	bool current = false;

	COLDIR GetCollisions(CELL board[maxX][maxY]);
	void Place();
	void QuitFalling(CELL board[maxX][maxY]);
	void Draw();
	void FallOne();
	void MoveRight();
	void MoveLeft();
};