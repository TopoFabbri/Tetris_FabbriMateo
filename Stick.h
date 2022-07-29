#pragma once

#include "Globals.h"

struct Stick
{
private:
	COORDS centerLeft = initPiecePos;
	COORDS left{ centerLeft.x - 1, centerLeft.y };
	COORDS centerRight{ centerLeft.x + 1, centerLeft.y };
	COORDS right{ centerLeft.x + 2, centerLeft.y };
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
	int color = BlackOnCyan;
	bool current = false;
	int lHalf = sqr;
	int rHalf = sqr;

	bool DownColliding(CELL board[maxX][maxY]);
	bool LeftColliding(CELL board[maxX][maxY]);
	bool RightColliding(CELL board[maxX][maxY]);
	bool CheckOverlapedCell(CELL board[maxX][maxY]);
	void UnKick(CELL board[maxX][maxY]);
	void Draw();
	void DrawAsNext();
	void Place();
	void QuitFalling(CELL board[maxX][maxY]);
	void FallOne();
	void MoveUp();
	void MoveRight();
	void MoveLeft();
	void RotateRight();
	void RotateLeft();
	void BurnOnBoard(CELL board[maxX][maxY]);
	void EraseFromBoard(CELL board[maxX][maxY]);
};