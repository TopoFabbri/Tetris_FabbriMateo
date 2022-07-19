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

const int objQty = 7;

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

KEYS GetKeys(char& inKey, char input[]);
bool CheckLines(CELL board[maxX][maxY], OBJECTS obj, OBJS curObj, int& score);
void FrameUpdate(CELL board[maxX][maxY], OBJECTS& obj, OBJS curObj, int score);
void ExecuteInput(char& inKey, char input[], OBJECTS& obj, CELL board[maxX][maxY], OBJS curObj, int score);
void DestroyLine(CELL board[maxX][maxY], int line, OBJECTS obj, OBJS curObj, int score);
void FallObject(OBJECTS& obj, CELL board[maxX][maxY], OBJS curObj);
void RotateObjectLeft(OBJECTS& obj, CELL board[maxX][maxY], OBJS curObj, int score);
void RotateObjectRight(OBJECTS& obj, CELL board[maxX][maxY], OBJS curObj, int score);
void MoveObjectLeft(OBJECTS& obj, CELL board[maxX][maxY], OBJS curObj, int score);
void MoveObjectRight(OBJECTS& obj, CELL board[maxX][maxY], OBJS curObj, int score);
void DropDown(OBJECTS& obj, CELL board[maxX][maxY], OBJS curObj);
void DrawObject(OBJECTS obj, CELL board[maxX][maxY], OBJS curObj);
void DrawFirstLine(int size);
void DrawLastLine(int size);
void DrawBoard(CELL board[maxX][maxY], OBJECTS obj, OBJS curObj, int score);
void ResetBoard(CELL board[maxX][maxY]);
void CheckChangeObject(OBJECTS& obj, OBJS& curObj, CELL board[maxX][maxY]);
void Play(char input[]);
void PlaceObjects(OBJECTS& obj, OBJS curObj);
void SetNewSpeed(int& frameUpdate);
void DrawScore(int score);