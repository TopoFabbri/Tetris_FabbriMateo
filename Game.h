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

const int objQty = 7;
const int timeBomb = 2000;

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
	int secsElapsed;
	int counter = 0;
};

struct OBJECTS
{
	T t;
	Square square;
	Stick stick;
	LLeft lLeft;
	LRight lRight;
	ZLeft zLeft;
	ZRight zRight;
};

struct GAMEDATA
{
	CELL board[maxX][maxY];
	OBJECTS obj;
	OBJS nextObj = (OBJS)(rand() % objQty + 1);
	OBJS curObj = (OBJS)(rand() % objQty + 1);
	bool lost;
	char inKey;
	int score = 0;
	int frameRate = defFrameUpdate;
	int frame = 0;
	int collisionTime;
	bool collided = false;
};

KEYS GetKeys(GAMEDATA& gData, char input[]);
bool CheckLines(GAMEDATA& gData);
bool ShouldDropFrame(TIME& gTime, GAMEDATA& gData);
void FrameUpdate(GAMEDATA& gData);
void ExecuteInput(GAMEDATA& gData, char input[]);
void DestroyLine(GAMEDATA& gData, int line);
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
void DrawBoard(GAMEDATA gData);
void DrawLine(GAMEDATA gData, int line);
void ResetBoard(CELL board[maxX][maxY]);
void CheckChangeObject(GAMEDATA& gData);
void Play(char input[]);
void PlaceObjects(GAMEDATA& gData);
void SetNewSpeed(GAMEDATA& gData, TIME gTime);
void CheckOverlaps(GAMEDATA& gData);
void DrawScore(int score);
void DrawNextObject(GAMEDATA gData);
void DrawFrames(GAMEDATA gData);