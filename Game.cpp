#include "Game.h"

void Play(char input[])
{
	CELL board[maxX][maxY];
	OBJECTS objects;
	char inKey = ' ';


	system("cls");
	ResetBoard(board);

	do
	{
		if (clock() % frameUpdate == 0)
			FrameUpdate(board, objects);

		ExecuteInput(inKey, input, objects, board);

	} while (inKey != input[(int)KEYS::Back]);
}

void FrameUpdate(CELL board[maxX][maxY], OBJECTS& obj)
{
	DrawBoard(board, obj);
	FallObject(obj, board);
}

void FallObject(OBJECTS& obj, CELL board[maxX][maxY])
{
	if (obj.t.GetCollisions(board) != COLDIR::Down)
	{
		obj.t.FallOne();
	}
}

void DrawObject(OBJECTS obj, CELL board[maxX][maxY])
{
	obj.t.Draw();
}

void MoveObjectLeft(OBJECTS& obj, CELL board[maxX][maxY])
{
	if (obj.t.GetCollisions(board) != COLDIR::Left)
	{
		obj.t.MoveLeft();
		DrawBoard(board, obj);
	}
}

void MoveObjectRight(OBJECTS& obj, CELL board[maxX][maxY])
{
	if (obj.t.GetCollisions(board) != COLDIR::Right)
	{
		obj.t.MoveRight();
		DrawBoard(board, obj);
	}
}

KEYS GetKeys(char& inKey, char input[])
{
	if (_kbhit())
	{
		inKey = _getch();

		if (inKey == input[(int)KEYS::Up])
		{
			return KEYS::Up;
		}
		else if (inKey == input[(int)KEYS::Left])
		{
			return KEYS::Left;
		}
		else if (inKey == input[(int)KEYS::Right])
		{
			return KEYS::Right;
		}
		else if (inKey == input[(int)KEYS::Down])
		{
			return KEYS::Down;
		}

		return KEYS::None;
	}
}

void ExecuteInput(char& inKey, char input[], OBJECTS& obj, CELL board[maxX][maxY])
{
	KEYS action = GetKeys(inKey, input);

	switch (action)
	{
	case KEYS::Up:
		break;

	case KEYS::Left:
		MoveObjectLeft(obj, board);
		break;

	case KEYS::Down:
		break;

	case KEYS::Right:
		MoveObjectRight(obj, board);
		break;

	case KEYS::Enter:
		break;

	case KEYS::Back:
		break;

	case KEYS::None:
		break;

	default:
		break;
	}
}

void DrawBoard(CELL board[maxX][maxY], OBJECTS obj)
{
	WALLS wall;
	CUR cursor;

	cursor.gotoxy(pos0);
	DrawFirstLine(maxX);

	for (int y = 0; y < maxY; y++)
	{
		std::cout << wall.ver;
		for (int x = 0; x < maxX; x++)
		{
			SetColor(board[x][y].color);
			std::cout << "  ";
			SetColor(defColor);
		}
		std::cout << wall.ver << std::endl;
	}

	DrawLastLine(maxX);
	DrawObject(obj, board);
}

void DrawFirstLine(int size)
{
	WALLS wall;

	std::cout << wall.upLeftC;

	for (int i = 0; i < size; i++)
	{
		std::cout << wall.hor << wall.hor;
	}

	std::cout << wall.upRightC << std::endl;
}

void DrawLastLine(int size)
{
	WALLS wall;

	std::cout << wall.lowLeftC;

	for (int i = 0; i < size; i++)
	{
		std::cout << wall.hor << wall.hor;
	}

	std::cout << wall.lowRightC << std::endl;
}

void ResetBoard(CELL board[maxX][maxY])
{
	for (int y = 0; y < maxY; y++)
	{
		for (int x = 0; x < maxX; x++)
		{
			board[x][y].color = defColor;
			board[x][y].state = CELLSTATE::Empty;
		}
	}
}