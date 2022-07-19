#pragma once

#include "Globals.h"

struct T
{
private:
	COORDS center = initPiecePos;
	COORDS left{ center.x - 1, center.y };
	COORDS right{ center.x + 1, center.y };
	COORDS down{ center.x, center.y + 1 };
	COLORS color = BlackOnPurple;
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