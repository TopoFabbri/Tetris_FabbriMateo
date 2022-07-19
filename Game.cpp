#include "Game.h"

void Play(char input[])
{
	CELL board[maxX][maxY];
	OBJECTS objects;
	OBJS curObj = (OBJS)(rand() % objQty + 1);
	bool lost = false;
	char inKey = '#';
	int score = 0;
	int frameUpdate = defFrameUpdate;

	system("cls");
	ResetBoard(board);
	PlaceObjects(objects, curObj);

	do
	{
		if (clock() % frameUpdate == 0)
			FrameUpdate(board, objects, curObj, score);

		ExecuteInput(inKey, input, objects, board, curObj, score);
		CheckChangeObject(objects, curObj, board);
		SetNewSpeed(frameUpdate);
		lost = CheckLines(board, objects, curObj, score);

	} while (inKey != input[(int)KEYS::Back] && !lost);
}

void FrameUpdate(CELL board[maxX][maxY], OBJECTS& obj, OBJS curObj, int score)
{
	DrawBoard(board, obj, curObj, score);
	FallObject(obj, board, curObj);
}

bool CheckLines(CELL board[maxX][maxY], OBJECTS obj, OBJS curObj, int& score)
{
	int rowsCleared = 0;
	for (int y = maxY - 1; y >= 0; y--)
	{
		bool fullLine = true;

		for (int x = 0; x < maxX; x++)
		{
			if (board[x][y].state == CELLSTATE::Empty)
			{
				fullLine = false;
				break;
			}
		}

		if (fullLine)
		{
			rowsCleared++;
			DestroyLine(board, y, obj, curObj, score);
		}
	}

	switch (rowsCleared)
	{
	case 1:
		score += 40;
		break;

	case 2:
		score += 100;
		break;

	case 3:
		score += 300;
		break;

	case 4:
		score += 1200;
		break;

	default:
		break;
	}

	DrawScore(score);

	for (int x = 0; x < maxX; x++)
	{
		if (board[x][0].state == CELLSTATE::Static)
			return true;
	}

	return false;
}

void DestroyLine(CELL board[maxX][maxY], int line, OBJECTS obj, OBJS curObj, int score)
{
	for (int x = 0; x < maxX; x++)
	{
		board[x][line].color = defColor;
		board[x][line].state = CELLSTATE::Empty;
	}
	DrawBoard(board, obj, curObj, score);

	for (int y = line; y > 0; y--)
	{
		for (int x = 0; x < maxX; x++)
		{
			board[x][y].color = board[x][y - 1].color;
			board[x][y].state = board[x][y - 1].state;
		}

		DrawBoard(board, obj, curObj, score);
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
		{
			obj.t.EraseFromBoard(board);
			obj.t.FallOne();
			obj.t.BurnOnBoard(board);
		}
		break;

	case OBJS::Square:
		if (obj.square.GetCollisions(board) != COLDIR::Down)
		{
			obj.square.EraseFromBoard(board);
			obj.square.FallOne();
			obj.square.BurnOnBoard(board);
		}
		break;

	case OBJS::Stick:
		if (obj.stick.GetCollisions(board) != COLDIR::Down)
		{
			obj.stick.EraseFromBoard(board);
			obj.stick.FallOne();
			obj.stick.BurnOnBoard(board);
		}
		break;

	case OBJS::LLeft:
		if (obj.lLeft.GetCollisions(board) != COLDIR::Down)
		{
			obj.lLeft.EraseFromBoard(board);
			obj.lLeft.FallOne();
			obj.lLeft.BurnOnBoard(board);
		}
		break;

	case OBJS::LRight:
		if (obj.lRight.GetCollisions(board) != COLDIR::Down)
		{
			obj.lRight.EraseFromBoard(board);
			obj.lRight.FallOne();
			obj.lRight.BurnOnBoard(board);
		}
		break;

	case OBJS::ZLeft:
		if (obj.zLeft.GetCollisions(board) != COLDIR::Down)
		{
			obj.zLeft.EraseFromBoard(board);
			obj.zLeft.FallOne();
			obj.zLeft.BurnOnBoard(board);
		}
		break;

	case OBJS::ZRight:
		if (obj.zRight.GetCollisions(board) != COLDIR::Down)
		{
			obj.zRight.EraseFromBoard(board);
			obj.zRight.FallOne();
			obj.zRight.BurnOnBoard(board);
		}
		break;

	default:
		break;
	}
}

void MoveObjectLeft(OBJECTS& obj, CELL board[maxX][maxY], OBJS curObj, int score)
{
	switch (curObj)
	{
	case OBJS::None:
		break;

	case OBJS::T:
		if (obj.t.GetCollisions(board) != COLDIR::Left)
		{
			obj.t.EraseFromBoard(board);
			obj.t.MoveLeft();
			obj.t.BurnOnBoard(board);
			DrawBoard(board, obj, curObj, score);
		}
		break;

	case OBJS::Square:
		if (obj.square.GetCollisions(board) != COLDIR::Left)
		{
			obj.square.EraseFromBoard(board);
			obj.square.MoveLeft();
			obj.square.BurnOnBoard(board);
			DrawBoard(board, obj, curObj, score);
		}
		break;

	case OBJS::Stick:
		if (obj.stick.GetCollisions(board) != COLDIR::Left)
		{
			obj.stick.EraseFromBoard(board);
			obj.stick.MoveLeft();
			obj.stick.BurnOnBoard(board);
			DrawBoard(board, obj, curObj, score);
		}
		break;

	case OBJS::LLeft:
		if (obj.lLeft.GetCollisions(board) != COLDIR::Left)
		{
			obj.lLeft.EraseFromBoard(board);
			obj.lLeft.MoveLeft();
			obj.lLeft.BurnOnBoard(board);
			DrawBoard(board, obj, curObj, score);
		}
		break;

	case OBJS::LRight:
		if (obj.lRight.GetCollisions(board) != COLDIR::Left)
		{
			obj.lRight.EraseFromBoard(board);
			obj.lRight.MoveLeft();
			obj.lRight.BurnOnBoard(board);
			DrawBoard(board, obj, curObj, score);
		}
		break;

	case OBJS::ZLeft:
		if (obj.zLeft.GetCollisions(board) != COLDIR::Left)
		{
			obj.zLeft.EraseFromBoard(board);
			obj.zLeft.MoveLeft();
			obj.zLeft.BurnOnBoard(board);
			DrawBoard(board, obj, curObj, score);
		}
		break;

	case OBJS::ZRight:
		if (obj.zRight.GetCollisions(board) != COLDIR::Left)
		{
			obj.zRight.EraseFromBoard(board);
			obj.zRight.MoveLeft();
			obj.zRight.BurnOnBoard(board);
			DrawBoard(board, obj, curObj, score);
		}
		break;

	default:
		break;
	}
}

void MoveObjectRight(OBJECTS& obj, CELL board[maxX][maxY], OBJS curObj, int score)
{
	switch (curObj)
	{
	case OBJS::None:
		break;

	case OBJS::T:
		if (obj.t.GetCollisions(board) != COLDIR::Right)
		{
			obj.t.EraseFromBoard(board);
			obj.t.MoveRight();
			obj.t.BurnOnBoard(board);
			DrawBoard(board, obj, curObj, score);
		}
		break;

	case OBJS::Square:
		if (obj.square.GetCollisions(board) != COLDIR::Right)
		{
			obj.square.EraseFromBoard(board);
			obj.square.MoveRight();
			obj.square.BurnOnBoard(board);
			DrawBoard(board, obj, curObj, score);
		}
		break;

	case OBJS::Stick:
		if (obj.stick.GetCollisions(board) != COLDIR::Right)
		{
			obj.stick.EraseFromBoard(board);
			obj.stick.MoveRight();
			obj.stick.BurnOnBoard(board);
			DrawBoard(board, obj, curObj, score);
		}
		break;

	case OBJS::LLeft:
		if (obj.lLeft.GetCollisions(board) != COLDIR::Right)
		{
			obj.lLeft.EraseFromBoard(board);
			obj.lLeft.MoveRight();
			obj.lLeft.BurnOnBoard(board);
			DrawBoard(board, obj, curObj, score);
		}
		break;

	case OBJS::LRight:
		if (obj.lRight.GetCollisions(board) != COLDIR::Right)
		{
			obj.lRight.EraseFromBoard(board);
			obj.lRight.MoveRight();
			obj.lRight.BurnOnBoard(board);
			DrawBoard(board, obj, curObj, score);
		}
		break;

	case OBJS::ZLeft:
		if (obj.zLeft.GetCollisions(board) != COLDIR::Right)
		{
			obj.zLeft.EraseFromBoard(board);
			obj.zLeft.MoveRight();
			obj.zLeft.BurnOnBoard(board);
			DrawBoard(board, obj, curObj, score);
		}
		break;

	case OBJS::ZRight:
		if (obj.zRight.GetCollisions(board) != COLDIR::Right)
		{
			obj.zRight.EraseFromBoard(board);
			obj.zRight.MoveRight();
			obj.zRight.BurnOnBoard(board);
			DrawBoard(board, obj, curObj, score);
		}
		break;

	default:
		break;
	}
}

void RotateObjectLeft(OBJECTS& obj, CELL board[maxX][maxY], OBJS curObj, int score)
{
	switch (curObj)
	{
	case OBJS::None:
		break;

	case OBJS::T:
		obj.t.EraseFromBoard(board);
		obj.t.RotateLeft();
		obj.t.BurnOnBoard(board);
		DrawBoard(board, obj, curObj, score);
		break;

	case OBJS::Square:
		break;

	case OBJS::Stick:
		obj.stick.EraseFromBoard(board);
		obj.stick.RotateLeft();
		obj.stick.BurnOnBoard(board);
		DrawBoard(board, obj, curObj, score);
		break;

	case OBJS::LLeft:
		obj.lLeft.EraseFromBoard(board);
		obj.lLeft.RotateLeft();
		obj.lLeft.BurnOnBoard(board);
		DrawBoard(board, obj, curObj, score);
		break;

	case OBJS::LRight:
		obj.lRight.EraseFromBoard(board);
		obj.lRight.RotateLeft();
		obj.lRight.BurnOnBoard(board);
		DrawBoard(board, obj, curObj, score);
		break;

	case OBJS::ZLeft:
		obj.zLeft.EraseFromBoard(board);
		obj.zLeft.RotateLeft();
		obj.zLeft.BurnOnBoard(board);
		DrawBoard(board, obj, curObj, score);
		break;

	case OBJS::ZRight:
		obj.zRight.EraseFromBoard(board);
		obj.zRight.RotateLeft();
		obj.zRight.BurnOnBoard(board);
		DrawBoard(board, obj, curObj, score);
		break;

	default:
		break;
	}
}

void RotateObjectRight(OBJECTS& obj, CELL board[maxX][maxY], OBJS curObj, int score)
{
	switch (curObj)
	{
	case OBJS::None:
		break;

	case OBJS::T:
		obj.t.EraseFromBoard(board);
		obj.t.RotateRight();
		obj.t.BurnOnBoard(board);
		DrawBoard(board, obj, curObj, score);
		break;

	case OBJS::Square:
		break;

	case OBJS::Stick:
		obj.stick.EraseFromBoard(board);
		obj.stick.RotateRight();
		obj.stick.BurnOnBoard(board);
		DrawBoard(board, obj, curObj, score);
		break;

	case OBJS::LLeft:
		obj.lLeft.EraseFromBoard(board);
		obj.lLeft.RotateRight();
		obj.lLeft.BurnOnBoard(board);
		DrawBoard(board, obj, curObj, score);
		break;

	case OBJS::LRight:
		obj.lRight.EraseFromBoard(board);
		obj.lRight.RotateRight();
		obj.lRight.BurnOnBoard(board);
		DrawBoard(board, obj, curObj, score);
		break;

	case OBJS::ZLeft:
		obj.zLeft.EraseFromBoard(board);
		obj.zLeft.RotateRight();
		obj.zLeft.BurnOnBoard(board);
		DrawBoard(board, obj, curObj, score);
		break;

	case OBJS::ZRight:
		obj.zRight.EraseFromBoard(board);
		obj.zRight.RotateRight();
		obj.zRight.BurnOnBoard(board);
		DrawBoard(board, obj, curObj, score);
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
				obj.t.EraseFromBoard(board);
				obj.t.FallOne();
			}
		}
		break;

	case OBJS::Square:
		for (int i = 0; i < maxY; i++)
		{
			if (obj.square.GetCollisions(board) != COLDIR::Down)
			{
				obj.square.EraseFromBoard(board);
				obj.square.FallOne();
			}
		}
		break;

	case OBJS::Stick:
		for (int i = 0; i < maxY; i++)
		{
			if (obj.stick.GetCollisions(board) != COLDIR::Down)
			{
				obj.stick.EraseFromBoard(board);
				obj.stick.FallOne();
			}
		}
		break;

	case OBJS::LLeft:
		for (int i = 0; i < maxY; i++)
		{
			if (obj.lLeft.GetCollisions(board) != COLDIR::Down)
			{
				obj.lLeft.EraseFromBoard(board);
				obj.lLeft.FallOne();
			}
		}
		break;

	case OBJS::LRight:
		for (int i = 0; i < maxY; i++)
		{
			if (obj.lRight.GetCollisions(board) != COLDIR::Down)
			{
				obj.lRight.EraseFromBoard(board);
				obj.lRight.FallOne();
			}
		}
		break;

	case OBJS::ZLeft:
		for (int i = 0; i < maxY; i++)
		{
			if (obj.zLeft.GetCollisions(board) != COLDIR::Down)
			{
				obj.zLeft.EraseFromBoard(board);
				obj.zLeft.FallOne();
			}
		}
		break;

	case OBJS::ZRight:
		for (int i = 0; i < maxY; i++)
		{
			if (obj.zRight.GetCollisions(board) != COLDIR::Down)
			{
				obj.zRight.EraseFromBoard(board);
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

void ExecuteInput(char& inKey, char input[], OBJECTS& obj, CELL board[maxX][maxY], OBJS curObj, int score)
{
	KEYS action = GetKeys(inKey, input);

	switch (action)
	{
	case KEYS::Up:
		break;

	case KEYS::Left:
		MoveObjectLeft(obj, board, curObj, score);
		break;

	case KEYS::Down:
		break;

	case KEYS::Right:
		MoveObjectRight(obj, board, curObj, score);
		break;

	case KEYS::Enter:
		break;

	case KEYS::Back:
		break;

	case KEYS::RotateL:
		RotateObjectLeft(obj, board, curObj, score);
		break;

	case KEYS::RotateR:
		RotateObjectRight(obj, board, curObj, score);
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

void DrawBoard(CELL board[maxX][maxY], OBJECTS obj, OBJS curObj, int score)
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

void DrawScore(int score)
{
	CUR cursor;
	COORDS scoreCounterPos = { 90, 5 };

	cursor.gotoxy(scoreCounterPos);
	std::cout << "Score: " << score << "    ";

	cursor.gotoxy(txtPos);
}