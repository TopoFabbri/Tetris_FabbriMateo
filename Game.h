#pragma once

#include "Globals.h"
#include "T.h"
#include "Square.h"
#include "Stick.h"
#include "LLeft.h"
#include "LRight.h"
#include "ZLeft.h"
#include "ZRight.h"
#include <conio.h>
#include <time.h>
#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <chrono>

const int objQty = 7;

enum class OBJS
{
	None,
	T,
	Square,
	Stick,
	LLeft,
	LRight,
	ZLeft,
	ZRight
};

struct TIME
{
	int init;
	int elapsed;
	int secsElapsed = 0;
	int speedUpTime = 10;
	int counter = 0;
	int pausedTime = 0;
	int pausedStartTime = 0;
};

struct OBJECTS
{
	T t;
	Square SQUARE;
	Stick stick;
	LLeft lLeft;
	LRight lRight;
	ZLeft zLeft;
	ZRight zRight;
};

struct SQUARE
{
	COORDS pos;
	COLORS color;
	int fallingSpeed = 1;
	bool inPlace = false;

	SQUARE Create(int posX, int initSpeed)
	{
		return { {posX, 0}, GetRandomColor(), initSpeed };
	}

	void Fall(CELL board[maxX][maxY])
	{
		CUR cur;
		cur.gotoxy(ConLoc(pos));
		SetColor(defColor);
		std::cout << "  ";

		for (int i = 0; i <= fallingSpeed; i++)
		{
			if (pos.y + 1 >= maxY || board[pos.x][pos.y + 1].state == CELLSTATE::Static)
			{
				board[pos.x][pos.y].state = CELLSTATE::Static;
				inPlace = true;
				break;
			}
			else
			{
				pos.y++;
			}
		}

		cur.gotoxy(ConLoc(pos));
		SetColor(color);
		std::cout << "  ";
		fallingSpeed++;

	}
};

struct GAMEDATA
{
	CELL board[maxX][maxY];
	OBJECTS obj;
	OBJS nextObj = (OBJS)(rand() % objQty + 1);
	OBJS curObj = (OBJS)(rand() % objQty + 1);
	bool lost;
	char inKey;
	int frames = 0;
	int speed = 1;
	int score = 0;
	int timeLimit = 1000;
	int collisionTime;
	bool collided = false;
};

KEYS GetKeys(GAMEDATA& gData, char input[]);
bool CheckLines(GAMEDATA& gData, TIME& gTime);
void FrameUpdate(GAMEDATA& gData, TIME& gTime);
void ExecuteInput(GAMEDATA& gData, char input[]);
void DestroyLine(GAMEDATA& gData, int line, TIME& gTime);
COLORS GetOpposite(COLORS color);
void FallObject(GAMEDATA& gData);
void RotateObjectLeft(GAMEDATA& gData);
void RotateObjectRight(GAMEDATA& gData);
void MoveObjectLeft(GAMEDATA& gData);
void MoveObjectRight(GAMEDATA& gData);
void DropDown(GAMEDATA& gData);
void DrawObject(GAMEDATA gData);
void DrawFirstLine(int size);
void DrawLastLine(int size);
void DrawBoard(GAMEDATA& gData);
void DrawControls(char input[]);
void DrawKeys(int& line, std::string txt, char key);
void DrawLine(GAMEDATA gData, int line);
void ResetBoard(CELL board[maxX][maxY]);
bool CheckChangeObject(GAMEDATA& gData);
void Play(char input[]);
void PlaceObjects(GAMEDATA& gData);
void SetNewSpeed(GAMEDATA& gData, TIME& gTime);
void CheckOverlaps(GAMEDATA& gData);
void FramesOnTitle(int frames);
void DrawScore(int score);
void DrawTime(int time);
void DrawNextObject(GAMEDATA gData);
void DrawLevel(GAMEDATA gData);
void DrawBox(COORDS size, COORDS pos, bool fill);
void DrawBox(COORDS size, COORDS pos, bool fill, std::string title);
void DrawOnBoard(std::string text, int score);
void EndFill(GAMEDATA& gData);