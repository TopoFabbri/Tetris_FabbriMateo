#pragma once

const int txtMaxLength = 10;
const int maxButtons = 10;
const int frameUpdate = 100;

struct CUR
{
	int x;
	int y;

	void SetCursorPosition()
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)x, (short)y });
	}

	void gotoxy(int valueX, int valueY)
	{
		x = valueX;
		y = valueY;
		SetCursorPosition();
	}
};