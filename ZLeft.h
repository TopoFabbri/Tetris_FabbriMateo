#pragma once

#include "Globals.h"

struct ZLeft
{
private:
	COORDS center = initPiecePos;
	COORDS left{ center.x - 1, center.y };
	COORDS downRight{ center.x + 1, center.y + 1 };
	COORDS down{ center.x, center.y + 1 };
	COLORS color = BlackOnRed;
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
};