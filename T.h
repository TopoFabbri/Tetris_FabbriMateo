#pragma once

#include "Globals.h"
enum class CELDIR
{

};

struct T
{
private:
	COORDS center = initPiecePos;
	COORDS left{ center.x - 1, center.y };
	COORDS right{ center.x + 1, center.y };
	COORDS down{ center.x, center.y + 1 };
	COLORS color = BlackOnPurple;

public:
	void Draw();
	void FallOne();
	void MoveRight();
	void MoveLeft();
	void RotateRight();
	void RotateLeft();
	void DropDown();
};