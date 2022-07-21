#pragma once

#include <iostream>
#include <Windows.h>

const int txtMaxLength = 10;
const int maxButtons = 10;
const int maxX = 10;
const int maxY = 24;
const int boardIndent = 60;
const char sqr = 177;// 32
const int defFrameUpdate = 1;

enum class ROT
{
	Up,
	Right,
	Down,
	Left,
};

struct COORDS
{
	int x;
	int y;
};

enum class COLDIR
{
	None,
	Left,
	Right,
	Down,
};

enum class KEYS
{
	Up,
	Left,
	Down,
	Right,
	Enter,
	Back,
	RotateL,
	RotateR,
	DropDown,
	None
};

enum COLORS
{
	BlackOnBlack = 0,
	BlueOnBlack = 9,
	GreenOnBlack = 2,
	RedOnBlack = 4,
	PurpleOnBlack = 5,
	YellowOnBlack = 6,
	GrayOnBlack = 8,
	CyanOnBlack = 11,
	OrangeOnBlack = 12,
	WhiteOnBlack = 15,
	BlackOnBlue = 16,
	BlackOnGreen = 32,
	BlackOnLightBlue = 48,
	BlackOnRed = 64,
	BlackOnPurple = 80,
	WhiteOnPurple = 87,
	BlackOnYellow = 96,
	BlackOnGray = 128,
	BlackOnCyan = 176,
	BlackOnOrange = 192,
	BlackOnWhite = 240,
	BlueOnWhite = 241,
	GreenOnWhite = 242,
	CyanOnWhite = 243,
	PurpleOnWhite = 245,
	YellowOnWhite = 246,
	OrangeOnWhite = 252,
};

enum class CELLSTATE
{
	Empty,
	Moving,
	Static
};

struct WALLS
{
	const char upLeftC = 201;						// ╔
	const char hor = 205;								// ═
	const char upT = 203;								// ╦
	const char upRightC = 187;							// ╗
	const char ver = 186;								// ║
	const char leftT = 204;								// ╠
	const char cross = 206;								// ╬
	const char rightT = 185;								// ╣
	const char lowLeftC = 200;							// ╚
	const char lowT = 202;								// ╩
	const char lowRightC = 188;							// ╝

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

const COLORS defColor = WhiteOnBlack;

struct CELL
{
	CELLSTATE state = CELLSTATE::Empty;
	COLORS color = defColor;
};

const COORDS initPiecePos{ 5, 0 };
const COORDS txtPos{ 0, 30 };
const COORDS pos0{ 0, 0 };

COORDS ConLoc(COORDS boardLoc);
void SetColor(COLORS color);
void hidecursor();
void SetFontSize(int sizeX, int sizeY);