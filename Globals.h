#pragma once

#include <Windows.h>

const int txtMaxLength = 10;
const int maxButtons = 10;
const int frameUpdate = 100;

struct COORDS
{
	int x;
	int y;
};

struct CUR
{
	int x;
	int y;

	void SetCursorPosition()
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)x, (short)y });
	}

	void gotoxy(COORDS loc)
	{
		x = loc.x;
		y = loc.y;
		SetCursorPosition();
	}
};

const COORDS initPiecePos{ 5, 0 };