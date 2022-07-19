#include "Game.h"

void Play(char input[])
{
	CELL board[maxX][maxY];
	OBJECTS objects;
	OBJS curObj = (OBJS)(rand() % objQty + 1);
	bool lost = false;
	char inKey = '#';
	int frameUpdate = defFrameUpdate;

	system("cls");
	ResetBoard(board);
	PlaceObjects(objects, curObj);

	do
	{
		if (clock() % frameUpdate == 0)
			FrameUpdate(board, objects, curObj);

		ExecuteInput(inKey, input, objects, board, curObj);
		CheckChangeObject(objects, curObj, board);
		SetNewSpeed(frameUpdate);
		lost = CheckLines(board, objects, curObj);

	} while (inKey != input[(int)KEYS::Back] && !lost);
}

void FrameUpdate(CELL board[maxX][maxY], OBJECTS& obj, OBJS curObj)
{
	DrawBoard(board, obj, curObj);
	FallObject(obj, board, curObj);
}

bool CheckLines(CELL board[maxX][maxY], OBJECTS obj, OBJS curObj)
{
	for (int y = maxY - 1; y >= 0; y--)
	{
		bool fullLine = true;

		for (int x = 0; x < maxX; x++)
		{
			if (board[x][y].state == CELLSTATE::Empty)
				fullLine = false;
		}

		if (fullLine)
			DestroyLine(board, y, obj, curObj);
	}

	for (int x = 0; x < maxX; x++)
	{
		if (board[x][0].state != CELLSTATE::Empty)
			return true;
	}

	return false;
}

void DestroyLine(CELL board[maxX][maxY], int line, OBJECTS obj, OBJS curObj)
{
	for (int x = 0; x < maxX; x++)
	{
		board[x][line].color = defColor;
		board[x][line].state = CELLSTATE::Empty;
	}
	DrawBoard(board, obj, curObj);

	for (int y = line; y > 0; y--)
	{
		for (int x = 0; x < maxX; x++)
		{
			board[x][y].color = board[x][y - 1].color;
			board[x][y].state = board[x][y - 1].state;
		}

		DrawBoard(board, obj, curObj);
	}
}

void FallObject(OBJECTS& obj, CELL board[maxX][maxY], OBJS curObj)
{
	switch (curObj)
	{
	case OBJS::None:
		break;

	case OBJS::T:
		if (obj.t.GetCollisions(board) != COLDIR::Down)
			obj.t.FallOne();
		break;

	case OBJS::Square:
		if (obj.square.GetCollisions(board) != COLDIR::Down)
			obj.square.FallOne();
		break;

	case OBJS::Stick:
		if (obj.stick.GetCollisions(board) != COLDIR::Down)
			obj.stick.FallOne();
		break;

	case OBJS::LLeft:
		if (obj.lLeft.GetCollisions(board) != COLDIR::Down)
			obj.lLeft.FallOne();
		break;

	case OBJS::LRight:
		if (obj.lRight.GetCollisions(board) != COLDIR::Down)
			obj.lRight.FallOne();
		break;

	case OBJS::ZLeft:
		if (obj.zLeft.GetCollisions(board) != COLDIR::Down)
			obj.zLeft.FallOne();
		break;

	case OBJS::ZRight:
		if (obj.zRight.GetCollisions(board) != COLDIR::Down)
			obj.zRight.FallOne();
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
		if (obj.stick.GetCollisions(board) != COLDIR::Left)
		{
			obj.stick.MoveLeft();
			DrawBoard(board, obj, curObj);
		}
		break;

	case OBJS::LLeft:
		if (obj.lLeft.GetCollisions(board) != COLDIR::Left)
		{
			obj.lLeft.MoveLeft();
			DrawBoard(board, obj, curObj);
		}
		break;

	case OBJS::LRight:
		if (obj.lRight.GetCollisions(board) != COLDIR::Left)
		{
			obj.lRight.MoveLeft();
			DrawBoard(board, obj, curObj);
		}
		break;

	case OBJS::ZLeft:
		if (obj.zLeft.GetCollisions(board) != COLDIR::Left)
		{
			obj.zLeft.MoveLeft();
			DrawBoard(board, obj, curObj);
		}
		break;

	case OBJS::ZRight:
		if (obj.zRight.GetCollisions(board) != COLDIR::Left)
		{
			obj.zRight.MoveLeft();
			DrawBoard(board, obj, curObj);
		}
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
		if (obj.stick.GetCollisions(board) != COLDIR::Right)
		{
			obj.stick.MoveRight();
			DrawBoard(board, obj, curObj);
		}
		break;

	case OBJS::LLeft:
		if (obj.lLeft.GetCollisions(board) != COLDIR::Right)
		{
			obj.lLeft.MoveRight();
			DrawBoard(board, obj, curObj);
		}
		break;

	case OBJS::LRight:
		if (obj.lRight.GetCollisions(board) != COLDIR::Right)
		{
			obj.lRight.MoveRight();
			DrawBoard(board, obj, curObj);
		}
		break;

	case OBJS::ZLeft:
		if (obj.zLeft.GetCollisions(board) != COLDIR::Right)
		{
			obj.zLeft.MoveRight();
			DrawBoard(board, obj, curObj);
		}
		break;

	case OBJS::ZRight:
		if (obj.zRight.GetCollisions(board) != COLDIR::Right)
		{
			obj.zRight.MoveRight();
			DrawBoard(board, obj, curObj);
		}
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
		obj.stick.RotateLeft();
		DrawBoard(board, obj, curObj);
		break;

	case OBJS::LLeft:
		obj.lLeft.RotateLeft();
		DrawBoard(board, obj, curObj);
		break;

	case OBJS::LRight:
		obj.lRight.RotateLeft();
		DrawBoard(board, obj, curObj);
		break;

	case OBJS::ZLeft:
		obj.zLeft.RotateLeft();
		DrawBoard(board, obj, curObj);
		break;

	case OBJS::ZRight:
		obj.zRight.RotateLeft();
		DrawBoard(board, obj, curObj);
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
		obj.stick.RotateRight();
		DrawBoard(board, obj, curObj);
		break;

	case OBJS::LLeft:
		obj.lLeft.RotateRight();
		DrawBoard(board, obj, curObj);
		break;

	case OBJS::LRight:
		obj.lRight.RotateRight();
		DrawBoard(board, obj, curObj);
		break;

	case OBJS::ZLeft:
		obj.zLeft.RotateRight();
		DrawBoard(board, obj, curObj);
		break;

	case OBJS::ZRight:
		obj.zRight.RotateRight();
		DrawBoard(board, obj, curObj);
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
			}
		}
		break;

	case OBJS::Square:
		for (int i = 0; i < maxY; i++)
		{
			if (obj.square.GetCollisions(board) != COLDIR::Down)
			{
				obj.square.FallOne();
			}
		}
		break;

	case OBJS::Stick:
		for (int i = 0; i < maxY; i++)
		{
			if (obj.stick.GetCollisions(board) != COLDIR::Down)
			{
				obj.stick.FallOne();
			}
		}
		break;

	case OBJS::LLeft:
		for (int i = 0; i < maxY; i++)
		{
			if (obj.lLeft.GetCollisions(board) != COLDIR::Down)
			{
				obj.lLeft.FallOne();
			}
		}
		break;

	case OBJS::LRight:
		for (int i = 0; i < maxY; i++)
		{
			if (obj.lRight.GetCollisions(board) != COLDIR::Down)
			{
				obj.lRight.FallOne();
			}
		}
		break;

	case OBJS::ZLeft:
		for (int i = 0; i < maxY; i++)
		{
			if (obj.zLeft.GetCollisions(board) != COLDIR::Down)
			{
				obj.zLeft.FallOne();
			}
		}
		break;

	case OBJS::ZRight:
		for (int i = 0; i < maxY; i++)
		{
			if (obj.zRight.GetCollisions(board) != COLDIR::Down)
			{
				obj.zRight.FallOne();
			}
		}
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
		obj.stick.Draw();
		break;

	case OBJS::LLeft:
		obj.lLeft.Draw();
		break;

	case OBJS::LRight:
		obj.lRight.Draw();
		break;

	case OBJS::ZLeft:
		obj.zLeft.Draw();
		break;

	case OBJS::ZRight:
		obj.zRight.Draw();
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
	}

	return KEYS::None;
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
		if (!obj.stick.current)
		{
			curObj = (OBJS)(rand() % objQty + 1);
			PlaceObjects(obj, curObj);
		}
		break;

	case OBJS::LLeft:
		if (!obj.lLeft.current)
		{
			curObj = (OBJS)(rand() % objQty + 1);
			PlaceObjects(obj, curObj);
		}
		break;

	case OBJS::LRight:
		if (!obj.lRight.current)
		{
			curObj = (OBJS)(rand() % objQty + 1);
			PlaceObjects(obj, curObj);
		}
		break;

	case OBJS::ZLeft:
		if (!obj.zLeft.current)
		{
			curObj = (OBJS)(rand() % objQty + 1);
			PlaceObjects(obj, curObj);
		}
		break;

	case OBJS::ZRight:
		if (!obj.zRight.current)
		{
			curObj = (OBJS)(rand() % objQty + 1);
			PlaceObjects(obj, curObj);
		}
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
		for (int i = 0; i < boardIndent; i++)
		{
			std::cout << " ";
		}

		std::cout << wall.ver;
		for (int x = 0; x < maxX; x++)
		{
			SetColor(board[x][y].color);

			if (board[x][y].state == CELLSTATE::Empty)
				std::cout << "  ";
			else
				std::cout << sqr << sqr;

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

	for (int i = 0; i < boardIndent; i++)
	{
		std::cout << " ";
	}

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

	for (int i = 0; i < boardIndent; i++)
	{
		std::cout << " ";
	}

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
		obj.stick.Place();
		break;

	case OBJS::LLeft:
		obj.lLeft.Place();
		break;

	case OBJS::LRight:
		obj.lRight.Place();
		break;

	case OBJS::ZLeft:
		obj.zLeft.Place();
		break;

	case OBJS::ZRight:
		obj.zRight.Place();
		break;

	default:
		break;
	}
}

void SetNewSpeed(int& frameUpdate)
{
	int speedUpdateTime = 20000;

	if (frameUpdate > 200 && clock() % speedUpdateTime == 0)
		frameUpdate /= 2;
}