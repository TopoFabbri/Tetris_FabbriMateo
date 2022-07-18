#pragma once

#include "Globals.h"
#include "T.h"
#include <conio.h>

struct OBJECTS
{
	T t;
};

KEYS GetKeys(char& inKey, char input[]);
void ExecuteInput(char& inKey, char input[], OBJECTS& obj, CELL board[maxX][maxY]);
void FallObject(OBJECTS& obj, CELL board[maxX][maxY]);
void MoveObjectLeft(OBJECTS& obj, CELL board[maxX][maxY]);
void MoveObjectRight(OBJECTS& obj, CELL board[maxX][maxY]);
void FrameUpdate(CELL board[maxX][maxY], OBJECTS& obj);
void DrawFirstLine(int size);
void DrawLastLine(int size);
void DrawBoard(CELL board[maxX][maxY], OBJECTS obj);
void ResetBoard(CELL board[maxX][maxY]);
void Play(char input[]);