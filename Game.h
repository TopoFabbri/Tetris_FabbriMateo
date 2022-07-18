#pragma once

#include "Globals.h"
#include "T.h"
#include <conio.h>

const int maxX = 10;
const int maxY = 24;

enum class CELLSTATE
{
	Empty,
	Static,
	Moving
};

struct OBJECTS
{
	T t;
};

KEYS GetKeys(char& inKey, char input[]);
void ExecuteInput(char& inKey, char input[], OBJECTS& obj, char board[maxX][maxY]);
void FallObject(OBJECTS& obj);
void MoveObjectLeft(OBJECTS& obj, char board[maxX][maxY]);
void MoveObjectRight(OBJECTS& obj, char board[maxX][maxY]);
void FrameUpdate(char board[maxX][maxY], OBJECTS& obj);
void DrawFirstLine(int size);
void DrawLastLine(int size);
void DrawBoard(char board[maxX][maxY], OBJECTS obj);
void ResetBoard(char board[maxX][maxY]);
void Play(char input[]);