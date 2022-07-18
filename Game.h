#pragma once

#include "Globals.h"
#include "T.h"
#include "Square.h"
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

const int objQty = 2;

struct OBJECTS
{
	T t;
	Square square;
};

KEYS GetKeys(char& inKey, char input[]);
void FrameUpdate(CELL board[maxX][maxY], OBJECTS& obj, OBJS curObj);
void ExecuteInput(char& inKey, char input[], OBJECTS& obj, CELL board[maxX][maxY], OBJS curObj);
void FallObject(OBJECTS& obj, CELL board[maxX][maxY], OBJS curObj);
void RotateObjectLeft(OBJECTS& obj, CELL board[maxX][maxY], OBJS curObj);
void RotateObjectRight(OBJECTS& obj, CELL board[maxX][maxY], OBJS curObj);
void MoveObjectLeft(OBJECTS& obj, CELL board[maxX][maxY], OBJS curObj);
void MoveObjectRight(OBJECTS& obj, CELL board[maxX][maxY], OBJS curObj);
void DropDown(OBJECTS& obj, CELL board[maxX][maxY], OBJS curObj);
void DrawObject(OBJECTS obj, CELL board[maxX][maxY], OBJS curObj);
void DrawFirstLine(int size);
void DrawLastLine(int size);
void DrawBoard(CELL board[maxX][maxY], OBJECTS obj, OBJS curObj);
void ResetBoard(CELL board[maxX][maxY]);
void CheckChangeObject(OBJECTS& obj, OBJS& curObj, CELL board[maxX][maxY]);
void Play(char input[]);
void PlaceObjects(OBJECTS& obj, OBJS curObj);