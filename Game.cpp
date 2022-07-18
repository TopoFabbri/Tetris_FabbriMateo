#include "Game.h"

void Play(char input[])
{
	CELL board[maxX][maxY];
	OBJECTS objects;
	OBJS curObj = (OBJS)(rand() % objQty + 1);
	char inKey = ' ';

	system("cls");
	ResetBoard(board);
	PlaceObjects(objects, curObj);

	do
	{
		if (clock() % frameUpdate == 0)
			FrameUpdate(board, objects, curObj);

		ExecuteInput(inKey, input, objects, board, curObj);
		CheckChangeObject(objects, curObj, board);

	} while (inKey != input[(int)KEYS::Back]);
}

void FrameUpdate(CELL board[maxX][maxY], OBJECTS& obj, OBJS curObj)
{
	DrawBoard(board, obj, curObj);
	FallObject(obj, board, curObj);
}

void FallObject(OBJECTS& obj, CELL board[maxX][maxY], OBJS curObj)
{
	switch (curObj)
	{
	case OBJS::None:
		break;

	case OBJS::T:
		if (obj.t.GetCollisions(board) != COLDIR::Down)
		{
			obj.t.FallOne();
		}
		break;

	case OBJS::Square:
		if (obj.square.GetCollisions(board) != COLDIR::Down)
		{
			obj.square.FallOne();
		}
		break;

	case OBJS::Stick:
		break;

	case OBJS::LLeft:
		break;

	case OBJS::LRight:
		break;

	case OBJS::ZLeft:
		break;

	case OBJS::ZRight:
		break;

	default:
		break;
	}
}

void MoveObjectLeft(OBJECTS& obj, CELL board[maxX][maxY], OBJS curObj)
{
	switch (curObj)
	{
	case OBJS::None:
		break;

	case OBJS::T:
		if (obj.t.GetCollisions(board) != COLDIR::Left)
		{
			obj.t.MoveLeft();
			DrawBoard(board, obj, curObj);
		}
		break;

	case OBJS::Square:
		if (obj.square.GetCollisions(board) != COLDIR::Left)
		{
			obj.square.MoveLeft();
			DrawBoard(board, obj, curObj);
		}
		break;

	case OBJS::Stick:
		break;

	case OBJS::LLeft:
		break;

	case OBJS::LRight:
		break;

	case OBJS::ZLeft:
		break;

	case OBJS::ZRight:
		break;

	default:
		break;
	}
}

void MoveObjectRight(OBJECTS& obj, CELL board[maxX][maxY], OBJS curObj)
{
	switch (curObj)
	{
	case OBJS::None:
		break;

	case OBJS::T:
		if (obj.t.GetCollisions(board) != COLDIR::Right)
		{
			obj.t.MoveRight();
			DrawBoard(board, obj, curObj);
		}
		break;

	case OBJS::Square:
		if (obj.square.GetCollisions(board) != COLDIR::Right)
		{
			obj.square.MoveRight();
			DrawBoard(board, obj, curObj);
		}
		break;

	case OBJS::Stick:
		break;

	case OBJS::LLeft:
		break;

	case OBJS::LRight:
		break;

	case OBJS::ZLeft:
		break;

	case OBJS::ZRight:
		break;

	default:
		break;
	}
}

void RotateObjectLeft(OBJECTS& obj, CELL board[maxX][maxY], OBJS curObj)
{
	switch (curObj)
	{
	case OBJS::None:
		break;

	case OBJS::T:
		obj.t.RotateLeft();
		DrawBoard(board, obj, curObj);
		break;

	case OBJS::Square:
		break;

	case OBJS::Stick:
		break;

	case OBJS::LLeft:
		break;

	case OBJS::LRight:
		break;

	case OBJS::ZLeft:
		break;

	case OBJS::ZRight:
		break;

	default:
		break;
	}
}

void RotateObjectRight(OBJECTS& obj, CELL board[maxX][maxY], OBJS curObj)
{
	switch (curObj)
	{
	case OBJS::None:
		break;

	case OBJS::T:
		obj.t.RotateRight();
		DrawBoard(board, obj, curObj);
		break;

	case OBJS::Square:
		break;

	case OBJS::Stick:
		break;

	case OBJS::LLeft:
		break;

	case OBJS::LRight:
		break;

	case OBJS::ZLeft:
		break;

	case OBJS::ZRight:
		break;

	default:
		break;
	}
}

void DropDown(OBJECTS& obj, CELL board[maxX][maxY], OBJS curObj)
{
	switch (curObj)
	{
	case OBJS::None:
		break;

	case OBJS::T:
		for (int i = 0; i < maxY; i++)
		{
			if (obj.t.GetCollisions(board) != COLDIR::Down)
			{
				obj.t.FallOne();
				DrawBoard(board, obj, curObj);
			}
		}
		break;

	case OBJS::Square:
		for (int i = 0; i < maxY; i++)
		{
			if (obj.square.GetCollisions(board) != COLDIR::Down)
			{
				obj.square.FallOne();
				DrawBoard(board, obj, curObj);
			}
		}
		break;

	case OBJS::Stick:
		break;

	case OBJS::LLeft:
		break;

	case OBJS::LRight:
		break;

	case OBJS::ZLeft:
		break;

	case OBJS::ZRight:
		break;

	default:
		break;
	}
}

void DrawObject(OBJECTS obj, CELL board[maxX][maxY], OBJS curObj)
{
	switch (curObj)
	{
	case OBJS::None:
		break;

	case OBJS::T:
		obj.t.Draw();
		break;

	case OBJS::Square:
		obj.square.Draw();
		break;

	case OBJS::Stick:
		break;

	case OBJS::LLeft:
		break;

	case OBJS::LRight:
		break;

	case OBJS::ZLeft:
		break;

	case OBJS::ZRight:
		break;

	default:
		break;
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
		else if (inKey == input[(int)KEYS::RotateL])
		{
			return KEYS::RotateL;
		}
		else if (inKey == input[(int)KEYS::RotateR])
		{
			return KEYS::RotateR;
		}
		else if (inKey == input[(int)KEYS::DropDown])
		{
			return KEYS::DropDown;
		}

		return KEYS::None;
	}
}

void ExecuteInput(char& inKey, char input[], OBJECTS& obj, CELL board[maxX][maxY], OBJS curObj)
{
	KEYS action = GetKeys(inKey, input);

	switch (action)
	{
	case KEYS::Up:
		break;

	case KEYS::Left:
		MoveObjectLeft(obj, board, curObj);
		break;

	case KEYS::Down:
		break;

	case KEYS::Right:
		MoveObjectRight(obj, board, curObj);
		break;

	case KEYS::Enter:
		break;

	case KEYS::Back:
		break;

	case KEYS::RotateL:
		RotateObjectLeft(obj, board, curObj);
		break;

	case KEYS::RotateR:
		RotateObjectRight(obj, board, curObj);
		break;

	case KEYS::DropDown:
		DropDown(obj, board, curObj);
		break;

	case KEYS::None:
		break;

	default:
		break;
	}
}

void CheckChangeObject(OBJECTS& obj, OBJS& curObj, CELL board[maxX][maxY])
{
	switch (curObj)
	{
	case OBJS::None:
		break;

	case OBJS::T:
		if (!obj.t.current)
		{
			curObj = (OBJS)(rand() % objQty + 1);
			PlaceObjects(obj, curObj);
		}
		break;

	case OBJS::Square:
		if (!obj.square.current)
		{
			curObj = (OBJS)(rand() % objQty + 1);
			PlaceObjects(obj, curObj);
		}
		break;

	case OBJS::Stick:
		break;

	case OBJS::LLeft:
		break;

	case OBJS::LRight:
		break;

	case OBJS::ZLeft:
		break;

	case OBJS::ZRight:
		break;

	default:
		break;
	}
}

void DrawBoard(CELL board[maxX][maxY], OBJECTS obj, OBJS curObj)
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
	DrawObject(obj, board, curObj);
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

void PlaceObjects(OBJECTS& obj, OBJS curObj)
{
	switch (curObj)
	{
	case OBJS::None:
		break;

	case OBJS::T:
		obj.t.Place();
		break;

	case OBJS::Square:
		obj.square.Place();
		break;

	case OBJS::Stick:
		break;

	case OBJS::LLeft:
		break;

	case OBJS::LRight:
		break;

	case OBJS::ZLeft:
		break;

	case OBJS::ZRight:
		break;

	default:
		break;
	}
}