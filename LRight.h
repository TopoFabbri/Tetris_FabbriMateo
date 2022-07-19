#pragma once

#include "Globals.h"

class LRight
{
private:
	COORDS center = initPiecePos;
	COORDS corner{ center.x - 1, center.y };
	COORDS right{ center.x + 1, center.y };
	COORDS down{ center.x - 1, center.y + 1 };
	COLORS color = BlackOnOrange;
	ROT rot = ROT::Up;

	bool DownCollideCell(CELL board[maxX][maxY], COORDS cell);
	bool LeftCollideCell(CELL board[maxX][maxY], COORDS cell);
	bool RightCollideCell(CELL board[maxX][maxY], COORDS cell);
	void SetRotation();
	void RotationUp();
	void RotationRight();
	void RotationLeft();
	void RotationDown();
	void Kick();

public:
	bool current = false;

	COLDIR GetCollisions(CELL board[maxX][maxY]);
	void Draw();
	void Place();
	void QuitFalling(CELL board[maxX][maxY]);
	void FallOne();
	void MoveRight();
	void MoveLeft();
	void RotateRight();
	void RotateLeft();
	void BurnOnBoard(CELL board[maxX][maxY]);
	void EraseFromBoard(CELL board[maxX][maxY]);
};