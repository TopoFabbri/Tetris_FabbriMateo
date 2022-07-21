#include "Game.h"

void Play(char input[])
{
	GAMEDATA gData;
	TIME gTime;

	system("cls");
	ResetBoard(gData.board);
	PlaceObjects(gData);
	DrawControls(input);

	gTime.init = clock();

	do
	{
		if (ShouldDropFrame(gTime, gData))
			FrameUpdate(gData);

		DrawLevel(gData);
		DrawBoard(gData);
		ExecuteInput(gData, input);
		CheckChangeObject(gData);
		SetNewSpeed(gData, gTime);
		gData.lost = CheckLines(gData);


	} while (gData.inKey != input[(int)KEYS::Back] && !gData.lost);

	DrawOnBoard("          You lose!", gData.score);
}

void FramesOnTitle(int frames)
{
	std::string tmp = "Tetris Frames: ";
	std::ostringstream str1;
	str1 << frames;

	tmp.append(str1.str());
	std::wstring tmp1 = std::wstring(tmp.begin(), tmp.end());

	LPCWSTR title = tmp1.c_str();
	SetConsoleTitleW(title);
}

bool ShouldDropFrame(TIME& gTime, GAMEDATA& gData)
{
	gTime.elapsed = clock() - gTime.init;
	gTime.secsElapsed = gTime.elapsed / 1000;

	if (gTime.secsElapsed > gTime.counter)
	{
		gData.frame = 0;
		gTime.counter++;
	}

	int fraction = 1000 / gData.frameRate;
	int fractionReached = (gTime.elapsed - gTime.secsElapsed * 1000) / fraction;

	fractionReached = (fractionReached < 1 ? 1 : fractionReached);

	bool callFrame = (fractionReached > gData.frame);
	return callFrame;
}

void FrameUpdate(GAMEDATA& gData)
{
	gData.frame++;
	FramesOnTitle(gData.frame);
	FallObject(gData);
}

bool CheckLines(GAMEDATA& gData)
{
	int rowsCleared = 0;
	bool end = false;

	do
	{
		for (int y = maxY - 1; y >= 0; y--)
		{
			bool fullLine = true;

			for (int x = 0; x < maxX; x++)
			{
				if (gData.board[x][y].state != CELLSTATE::Static)
				{
					fullLine = false;

					end = y <= 0;
					break;
				}

			}

			if (fullLine)
			{
				rowsCleared++;
				DestroyLine(gData, y);
				break;
			}
		}
	} while (!end);

	switch (rowsCleared)
	{
	case 1:
		gData.score += 40;
		break;

	case 2:
		gData.score += 100;
		break;

	case 3:
		gData.score += 300;
		break;

	case 4:
		gData.score += 1200;
		break;

	default:
		break;
	}

	DrawScore(gData.score);

	for (int x = 0; x < maxX; x++)
	{
		if (gData.board[x][0].state == CELLSTATE::Static)
		{
			return true;
		}
	}

	return false;
}

void DestroyLine(GAMEDATA& gData, int line)
{

	for (int x = 0; x < maxX; x++)
	{
		gData.board[x][line].color = GetOpposite(gData.board[x][line].color);
		gData.board[x][line].state = CELLSTATE::Empty;
	}
	DrawLine(gData, line);
	Sleep(150);

	for (int x = 0; x < maxX; x++)
	{
		gData.board[x][line].color = GetOpposite(gData.board[x][line].color);
	}
	DrawLine(gData, line);
	Sleep(150);

	for (int x = 0; x < maxX; x++)
	{
		gData.board[x][line].color = BlackOnWhite;
	}
	DrawLine(gData, line);
	Sleep(150);

	for (int x = 0; x < maxX; x++)
	{
		gData.board[x][line].color = defColor;
	}
	DrawLine(gData, line);

	for (int y = line; y > 0; y--)
	{
		for (int x = 0; x < maxX; x++)
		{
			gData.board[x][y].color = gData.board[x][y - 1].color;
			gData.board[x][y].state = gData.board[x][y - 1].state;
		}

		DrawLine(gData, y);
	}
}

COLORS GetOpposite(COLORS color)
{
	switch (color)
	{
	case BlackOnBlue:
		return BlackOnYellow;
		break;

	case BlackOnGreen:
		return BlackOnPurple;
		break;

	case BlackOnCyan:
		return BlackOnOrange;
		break;

	case BlackOnRed:
		return BlackOnLightBlue;
		break;

	case BlackOnPurple:
		return BlackOnGreen;
		break;

	case BlackOnOrange:
		return BlackOnCyan;
		break;

	case BlackOnYellow:
		return BlackOnBlue;
		break;

	default:
		break;
	}

	return defColor;
}

void FallObject(GAMEDATA& gData)
{
	switch (gData.curObj)
	{
	case OBJS::None:
		break;

	case OBJS::T:
		if (!gData.obj.t.DownColliding(gData.board))
		{
			gData.obj.t.EraseFromBoard(gData.board);
			gData.obj.t.FallOne();
			gData.obj.t.BurnOnBoard(gData.board);
		}
		else
		{
			gData.collisionTime = clock();
			gData.collided = true;
		}
		break;

	case OBJS::Square:
		if (!gData.obj.square.DownColliding(gData.board))
		{
			gData.obj.square.EraseFromBoard(gData.board);
			gData.obj.square.FallOne();
			gData.obj.square.BurnOnBoard(gData.board);
		}
		else
		{
			gData.collisionTime = clock();
			gData.collided = true;
		}
		break;

	case OBJS::Stick:
		if (!gData.obj.stick.DownColliding(gData.board))
		{
			gData.obj.stick.EraseFromBoard(gData.board);
			gData.obj.stick.FallOne();
			gData.obj.stick.BurnOnBoard(gData.board);
		}
		else
		{
			gData.collisionTime = clock();
			gData.collided = true;
		}
		break;

	case OBJS::LLeft:
		if (!gData.obj.lLeft.DownColliding(gData.board))
		{
			gData.obj.lLeft.EraseFromBoard(gData.board);
			gData.obj.lLeft.FallOne();
			gData.obj.lLeft.BurnOnBoard(gData.board);
		}
		else
		{
			gData.collisionTime = clock();
			gData.collided = true;
		}
		break;

	case OBJS::LRight:
		if (!gData.obj.lRight.DownColliding(gData.board))
		{
			gData.obj.lRight.EraseFromBoard(gData.board);
			gData.obj.lRight.FallOne();
			gData.obj.lRight.BurnOnBoard(gData.board);
		}
		else
		{
			gData.collisionTime = clock();
			gData.collided = true;
		}
		break;

	case OBJS::ZLeft:
		if (!gData.obj.zLeft.DownColliding(gData.board))
		{
			gData.obj.zLeft.EraseFromBoard(gData.board);
			gData.obj.zLeft.FallOne();
			gData.obj.zLeft.BurnOnBoard(gData.board);
		}
		else
		{
			gData.collisionTime = clock();
			gData.collided = true;
		}
		break;

	case OBJS::ZRight:
		if (!gData.obj.zRight.DownColliding(gData.board))
		{
			gData.obj.zRight.EraseFromBoard(gData.board);
			gData.obj.zRight.FallOne();
			gData.obj.zRight.BurnOnBoard(gData.board);
		}
		else
		{
			gData.collisionTime = clock();
			gData.collided = true;
		}
		break;

	default:
		break;
	}
}

void MoveObjectLeft(GAMEDATA& gData)
{
	switch (gData.curObj)
	{
	case OBJS::None:
		break;

	case OBJS::T:
		if (!gData.obj.t.LeftColliding(gData.board))
		{
			gData.obj.t.EraseFromBoard(gData.board);
			gData.obj.t.MoveLeft();
			gData.obj.t.BurnOnBoard(gData.board);

		}
		break;

	case OBJS::Square:
		if (!gData.obj.square.LeftColliding(gData.board))
		{
			gData.obj.square.EraseFromBoard(gData.board);
			gData.obj.square.MoveLeft();
			gData.obj.square.BurnOnBoard(gData.board);

		}
		break;

	case OBJS::Stick:
		if (!gData.obj.stick.LeftColliding(gData.board))
		{
			gData.obj.stick.EraseFromBoard(gData.board);
			gData.obj.stick.MoveLeft();
			gData.obj.stick.BurnOnBoard(gData.board);

		}
		break;

	case OBJS::LLeft:
		if (!gData.obj.lLeft.LeftColliding(gData.board))
		{
			gData.obj.lLeft.EraseFromBoard(gData.board);
			gData.obj.lLeft.MoveLeft();
			gData.obj.lLeft.BurnOnBoard(gData.board);

		}
		break;

	case OBJS::LRight:
		if (!gData.obj.lRight.LeftColliding(gData.board))
		{
			gData.obj.lRight.EraseFromBoard(gData.board);
			gData.obj.lRight.MoveLeft();
			gData.obj.lRight.BurnOnBoard(gData.board);

		}
		break;

	case OBJS::ZLeft:
		if (!gData.obj.zLeft.LeftColliding(gData.board))
		{
			gData.obj.zLeft.EraseFromBoard(gData.board);
			gData.obj.zLeft.MoveLeft();
			gData.obj.zLeft.BurnOnBoard(gData.board);

		}
		break;

	case OBJS::ZRight:
		if (!gData.obj.zRight.LeftColliding(gData.board))
		{
			gData.obj.zRight.EraseFromBoard(gData.board);
			gData.obj.zRight.MoveLeft();
			gData.obj.zRight.BurnOnBoard(gData.board);

		}
		break;

	default:
		break;
	}
}

void MoveObjectRight(GAMEDATA& gData)
{
	switch (gData.curObj)
	{
	case OBJS::None:
		break;

	case OBJS::T:
		if (!gData.obj.t.RightColliding(gData.board))
		{
			gData.obj.t.EraseFromBoard(gData.board);
			gData.obj.t.MoveRight();
			gData.obj.t.BurnOnBoard(gData.board);

		}
		break;

	case OBJS::Square:
		if (!gData.obj.square.RightColliding(gData.board))
		{
			gData.obj.square.EraseFromBoard(gData.board);
			gData.obj.square.MoveRight();
			gData.obj.square.BurnOnBoard(gData.board);

		}
		break;

	case OBJS::Stick:
		if (!gData.obj.stick.RightColliding(gData.board))
		{
			gData.obj.stick.EraseFromBoard(gData.board);
			gData.obj.stick.MoveRight();
			gData.obj.stick.BurnOnBoard(gData.board);

		}
		break;

	case OBJS::LLeft:
		if (!gData.obj.lLeft.RightColliding(gData.board))
		{
			gData.obj.lLeft.EraseFromBoard(gData.board);
			gData.obj.lLeft.MoveRight();
			gData.obj.lLeft.BurnOnBoard(gData.board);

		}
		break;

	case OBJS::LRight:
		if (!gData.obj.lRight.RightColliding(gData.board))
		{
			gData.obj.lRight.EraseFromBoard(gData.board);
			gData.obj.lRight.MoveRight();
			gData.obj.lRight.BurnOnBoard(gData.board);

		}
		break;

	case OBJS::ZLeft:
		if (!gData.obj.zLeft.RightColliding(gData.board))
		{
			gData.obj.zLeft.EraseFromBoard(gData.board);
			gData.obj.zLeft.MoveRight();
			gData.obj.zLeft.BurnOnBoard(gData.board);

		}
		break;

	case OBJS::ZRight:
		if (!gData.obj.zRight.RightColliding(gData.board))
		{
			gData.obj.zRight.EraseFromBoard(gData.board);
			gData.obj.zRight.MoveRight();
			gData.obj.zRight.BurnOnBoard(gData.board);

		}
		break;

	default:
		break;
	}
}

void RotateObjectLeft(GAMEDATA& gData)
{
	switch (gData.curObj)
	{
	case OBJS::None:
		break;

	case OBJS::T:
		gData.obj.t.EraseFromBoard(gData.board);
		gData.obj.t.RotateLeft();

		if (gData.obj.t.CheckOverlapedCell(gData.board))
			gData.obj.t.RotateRight();

		gData.obj.t.BurnOnBoard(gData.board);

		break;

	case OBJS::Square:
		break;

	case OBJS::Stick:
		gData.obj.stick.EraseFromBoard(gData.board);
		gData.obj.stick.RotateLeft();

		if (gData.obj.stick.CheckOverlapedCell(gData.board))
			gData.obj.stick.RotateRight();

		gData.obj.stick.BurnOnBoard(gData.board);

		break;

	case OBJS::LLeft:
		gData.obj.lLeft.EraseFromBoard(gData.board);
		gData.obj.lLeft.RotateLeft();

		if (gData.obj.lLeft.CheckOverlapedCell(gData.board))
			gData.obj.lLeft.RotateRight();

		gData.obj.lLeft.BurnOnBoard(gData.board);
		break;

	case OBJS::LRight:
		gData.obj.lRight.EraseFromBoard(gData.board);
		gData.obj.lRight.RotateLeft();

		if (gData.obj.lRight.CheckOverlapedCell(gData.board))
			gData.obj.lRight.RotateRight();

		gData.obj.lRight.BurnOnBoard(gData.board);
		break;

	case OBJS::ZLeft:
		gData.obj.zLeft.EraseFromBoard(gData.board);
		gData.obj.zLeft.RotateLeft();

		if (gData.obj.zLeft.CheckOverlapedCell(gData.board))
			gData.obj.zLeft.RotateRight();

		gData.obj.zLeft.BurnOnBoard(gData.board);
		break;

	case OBJS::ZRight:
		gData.obj.zRight.EraseFromBoard(gData.board);
		gData.obj.zRight.RotateLeft();

		if (gData.obj.zRight.CheckOverlapedCell(gData.board))
			gData.obj.zRight.RotateRight();

		gData.obj.zRight.BurnOnBoard(gData.board);
		break;

	default:
		break;
	}

	CheckOverlaps(gData);
}

void RotateObjectRight(GAMEDATA& gData)
{
	switch (gData.curObj)
	{
	case OBJS::None:
		break;

	case OBJS::T:
		gData.obj.t.EraseFromBoard(gData.board);
		gData.obj.t.RotateRight();

		if (gData.obj.t.CheckOverlapedCell(gData.board))
			gData.obj.t.RotateLeft();

		gData.obj.t.BurnOnBoard(gData.board);

		break;

	case OBJS::Square:
		break;

	case OBJS::Stick:
		gData.obj.stick.EraseFromBoard(gData.board);
		gData.obj.stick.RotateRight();

		if (gData.obj.stick.CheckOverlapedCell(gData.board))
			gData.obj.stick.RotateLeft();

		gData.obj.stick.BurnOnBoard(gData.board);

		break;

	case OBJS::LLeft:
		gData.obj.lLeft.EraseFromBoard(gData.board);
		gData.obj.lLeft.RotateRight();

		if (gData.obj.lLeft.CheckOverlapedCell(gData.board))
			gData.obj.lLeft.RotateLeft();

		gData.obj.lLeft.BurnOnBoard(gData.board);

		break;

	case OBJS::LRight:
		gData.obj.lRight.EraseFromBoard(gData.board);
		gData.obj.lRight.RotateRight();

		if (gData.obj.lRight.CheckOverlapedCell(gData.board))
			gData.obj.lRight.RotateLeft();

		gData.obj.lRight.BurnOnBoard(gData.board);

		break;

	case OBJS::ZLeft:
		gData.obj.zLeft.EraseFromBoard(gData.board);
		gData.obj.zLeft.RotateRight();

		if (gData.obj.zLeft.CheckOverlapedCell(gData.board))
			gData.obj.zLeft.RotateLeft();

		gData.obj.zLeft.BurnOnBoard(gData.board);

		break;

	case OBJS::ZRight:
		gData.obj.zRight.EraseFromBoard(gData.board);
		gData.obj.zRight.RotateRight();

		if (gData.obj.zRight.CheckOverlapedCell(gData.board))
			gData.obj.zRight.RotateLeft();

		gData.obj.zRight.BurnOnBoard(gData.board);

		break;

	default:
		break;
	}
}

void DropDown(GAMEDATA& gData)
{
	switch (gData.curObj)
	{
	case OBJS::None:
		break;

	case OBJS::T:
		for (int i = 0; i < maxY; i++)
		{
			if (!gData.obj.t.DownColliding(gData.board))
			{
				gData.obj.t.EraseFromBoard(gData.board);
				gData.obj.t.FallOne();
			}
		}
		break;

	case OBJS::Square:
		for (int i = 0; i < maxY; i++)
		{
			if (!gData.obj.square.DownColliding(gData.board))
			{
				gData.obj.square.EraseFromBoard(gData.board);
				gData.obj.square.FallOne();
			}
		}
		break;

	case OBJS::Stick:
		for (int i = 0; i < maxY; i++)
		{
			if (!gData.obj.stick.DownColliding(gData.board))
			{
				gData.obj.stick.EraseFromBoard(gData.board);
				gData.obj.stick.FallOne();
			}
		}
		break;

	case OBJS::LLeft:
		for (int i = 0; i < maxY; i++)
		{
			if (!gData.obj.lLeft.DownColliding(gData.board))
			{
				gData.obj.lLeft.EraseFromBoard(gData.board);
				gData.obj.lLeft.FallOne();
			}
		}
		break;

	case OBJS::LRight:
		for (int i = 0; i < maxY; i++)
		{
			if (!gData.obj.lRight.DownColliding(gData.board))
			{
				gData.obj.lRight.EraseFromBoard(gData.board);
				gData.obj.lRight.FallOne();
			}
		}
		break;

	case OBJS::ZLeft:
		for (int i = 0; i < maxY; i++)
		{
			if (!gData.obj.zLeft.DownColliding(gData.board))
			{
				gData.obj.zLeft.EraseFromBoard(gData.board);
				gData.obj.zLeft.FallOne();
			}
		}
		break;

	case OBJS::ZRight:
		for (int i = 0; i < maxY; i++)
		{
			if (!gData.obj.zRight.DownColliding(gData.board))
			{
				gData.obj.zRight.EraseFromBoard(gData.board);
				gData.obj.zRight.FallOne();
			}
		}
		break;

	default:
		break;
	}

	DrawBoard(gData);
}

void DrawObject(GAMEDATA gData)
{
	switch (gData.curObj)
	{
	case OBJS::None:
		break;

	case OBJS::T:
		gData.obj.t.Draw();
		break;

	case OBJS::Square:
		gData.obj.square.Draw();
		break;

	case OBJS::Stick:
		gData.obj.stick.Draw();
		break;

	case OBJS::LLeft:
		gData.obj.lLeft.Draw();
		break;

	case OBJS::LRight:
		gData.obj.lRight.Draw();
		break;

	case OBJS::ZLeft:
		gData.obj.zLeft.Draw();
		break;

	case OBJS::ZRight:
		gData.obj.zRight.Draw();
		break;

	default:
		break;
	}
}

void DrawNextObject(GAMEDATA gData)
{
	CUR cursor;
	COORDS loc{ boardIndent + 12 + maxX,  0 };
	WALLS wall;
	const int length = 8;
	const int height = 2;

	SetColor(defColor);
	cursor.gotoxy(loc);

	std::cout << wall.upLeftC;
	for (int i = 0; i < length; i++)
	{
		std::cout << wall.hor;
	}
	std::cout << wall.upRightC;

	loc.y++;
	cursor.gotoxy(loc);
	std::cout << wall.ver << "  NEXT  " << wall.ver;

	loc.y++;
	cursor.gotoxy(loc);
	std::cout << wall.leftT;
	for (int i = 0; i < length; i++)
	{
		std::cout << wall.hor;
	}
	std::cout << wall.rightT;

	for (int i = 0; i < height; i++)
	{
		loc.y++;
		cursor.gotoxy(loc);
		std::cout << wall.ver << "        " << wall.ver;
	}

	loc.y++;
	cursor.gotoxy(loc);
	std::cout << wall.lowLeftC;
	for (int i = 0; i < length; i++)
	{
		std::cout << wall.hor;
	}
	std::cout << wall.lowRightC;

	switch (gData.nextObj)
	{
	case OBJS::None:
		break;

	case OBJS::T:
		gData.obj.t.DrawAsNext();
		break;

	case OBJS::Square:
		gData.obj.square.DrawAsNext();
		break;

	case OBJS::Stick:
		gData.obj.stick.DrawAsNext();
		break;

	case OBJS::LLeft:
		gData.obj.lLeft.DrawAsNext();
		break;

	case OBJS::LRight:
		gData.obj.lRight.DrawAsNext();
		break;

	case OBJS::ZLeft:
		gData.obj.zLeft.DrawAsNext();
		break;

	case OBJS::ZRight:
		gData.obj.zRight.DrawAsNext();
		break;

	default:
		break;
	}
}

KEYS GetKeys(GAMEDATA& gData, char input[])
{
	if (_kbhit())
	{
		gData.inKey = _getch();

		if (gData.inKey == input[(int)KEYS::Up])
		{
			return KEYS::Up;
		}
		else if (gData.inKey == input[(int)KEYS::Left])
		{
			return KEYS::Left;
		}
		else if (gData.inKey == input[(int)KEYS::Right])
		{
			return KEYS::Right;
		}
		else if (gData.inKey == input[(int)KEYS::Down])
		{
			return KEYS::Down;
		}
		else if (gData.inKey == input[(int)KEYS::RotateL])
		{
			return KEYS::RotateL;
		}
		else if (gData.inKey == input[(int)KEYS::RotateR])
		{
			return KEYS::RotateR;
		}
		else if (gData.inKey == input[(int)KEYS::DropDown])
		{
			return KEYS::DropDown;
		}
	}

	return KEYS::None;
}

void ExecuteInput(GAMEDATA& gData, char input[])
{
	KEYS action = GetKeys(gData, input);

	switch (action)
	{
	case KEYS::Up:
		break;

	case KEYS::Left:
		MoveObjectLeft(gData);
		break;

	case KEYS::Down:
		FallObject(gData);
		break;

	case KEYS::Right:
		MoveObjectRight(gData);
		break;

	case KEYS::Enter:
		break;

	case KEYS::Back:
		break;

	case KEYS::RotateL:
		RotateObjectLeft(gData);
		break;

	case KEYS::RotateR:
		RotateObjectRight(gData);
		break;

	case KEYS::DropDown:
		DropDown(gData);
		break;

	case KEYS::None:
		break;

	default:
		break;
	}
}

void CheckChangeObject(GAMEDATA& gData)
{
	int extraTime = clock() - gData.collisionTime;

	switch (gData.curObj)
	{
	case OBJS::None:
		break;

	case OBJS::T:
		if (!gData.obj.t.current)
		{
			gData.collided = false;

			gData.curObj = gData.nextObj;
			gData.nextObj = (OBJS)(rand() % objQty + 1);
			PlaceObjects(gData);
		}
		break;

	case OBJS::Square:
		if (!gData.obj.square.current)
		{
			gData.curObj = gData.nextObj;
			gData.nextObj = (OBJS)(rand() % objQty + 1);
			PlaceObjects(gData);
		}
		break;

	case OBJS::Stick:
		if (!gData.obj.stick.current)
		{
			gData.curObj = gData.nextObj;
			gData.nextObj = (OBJS)(rand() % objQty + 1);
			PlaceObjects(gData);
		}
		break;

	case OBJS::LLeft:
		if (!gData.obj.lLeft.current)
		{
			gData.curObj = gData.nextObj;
			gData.nextObj = (OBJS)(rand() % objQty + 1);
			PlaceObjects(gData);
		}
		break;

	case OBJS::LRight:
		if (!gData.obj.lRight.current)
		{
			gData.curObj = gData.nextObj;
			gData.nextObj = (OBJS)(rand() % objQty + 1);
			PlaceObjects(gData);
		}
		break;

	case OBJS::ZLeft:
		if (!gData.obj.zLeft.current)
		{
			gData.curObj = gData.nextObj;
			gData.nextObj = (OBJS)(rand() % objQty + 1);
			PlaceObjects(gData);
		}
		break;

	case OBJS::ZRight:
		if (!gData.obj.zRight.current)
		{
			gData.curObj = gData.nextObj;
			gData.nextObj = (OBJS)(rand() % objQty + 1);
			PlaceObjects(gData);
		}
		break;

	default:
		break;
	}
}

void DrawBoard(GAMEDATA gData)
{
	WALLS wall;
	CUR cursor;

	cursor.gotoxy(pos0);
	DrawFirstLine(maxX);

	for (int y = 0; y < maxY; y++)
	{
		cursor.gotoxy({ boardIndent, y });
		DrawLine(gData, y);
	}

	DrawLastLine(maxX);
	DrawObject(gData);
}

void DrawControls(char input[])
{
	COORDS loc = { 2, 1 };
	CUR cursor;
	WALLS wall;
	const int length = 25;
	const int lines = 11;

	cursor.gotoxy(loc);
	std::cout << wall.upLeftC;
	for (int i = 0; i < length - 1; i++)
	{
		std::cout << wall.hor;
	}
	std::cout << wall.upRightC;

	loc.y++;

	cursor.gotoxy(loc);
	std::cout << wall.ver << "        CONTROLS        " << wall.ver;

	loc.y++;

	cursor.gotoxy(loc);
	std::cout << wall.leftT;
	for (int i = 0; i < length - 1; i++)
	{
		std::cout << wall.hor;
	}
	std::cout << wall.rightT;

	loc.y++;

	for (int i = 0; i < lines; i++)
	{
		cursor.gotoxy({ loc.x, loc.y + i });
		std::cout << wall.ver;
	}

	for (int i = 0; i < lines; i++)
	{
		cursor.gotoxy({ loc.x + length, loc.y + i });
		std::cout << wall.ver;
	}

	cursor.gotoxy({ loc.x, loc.y + lines });
	std::cout << wall.lowLeftC;
	for (int i = 0; i < length - 1; i++)
	{
		std::cout << wall.hor;
	}
	std::cout << wall.lowRightC;

	loc.x += 2;

	cursor.gotoxy(loc);
	SetColor(BlueOnBlack);
	std::cout << "Movement:";
	loc.y++;

	DrawKeys(loc.y, "Move Left", input[(int)KEYS::Left]);
	DrawKeys(loc.y, "Move Right", input[(int)KEYS::Right]);

	loc.y ++;

	cursor.gotoxy(loc);
	SetColor(GreenOnBlack);
	std::cout << "Rotation:";
	loc.y++;

	DrawKeys(loc.y, "Rotate Left", input[(int)KEYS::RotateL]);
	DrawKeys(loc.y, "Rotate Right", input[(int)KEYS::RotateR]);

	loc.y ++;

	cursor.gotoxy(loc);
	SetColor(RedOnBlack);
	std::cout << "Mechanics:";
	loc.y++;

	DrawKeys(loc.y, "Drop Down", input[(int)KEYS::DropDown]);
	DrawKeys(loc.y, "Hard Drop", input[(int)KEYS::Down]);

	SetColor(defColor);
}

void DrawKeys(int& line, std::string txt, char key)
{
	CUR cur;
	int posX = 10;

	cur.gotoxy({ posX, line });
	std::cout << "'" << key << "': " << txt;

	line++;
}

void DrawLine(GAMEDATA gData, int line)
{
	WALLS wall;
	CUR cursor;

	cursor.gotoxy({ boardIndent, line + 1 });
	std::cout << wall.ver;
	for (int x = 0; x < maxX; x++)
	{
		SetColor(gData.board[x][line].color);

		if (gData.board[x][line].state == CELLSTATE::Empty)
			std::cout << "  ";
		else
			std::cout << sqr << sqr;

		SetColor(defColor);
	}
	std::cout << wall.ver << std::endl;
}

void DrawFirstLine(int size)
{
	CUR cursor;
	WALLS wall;

	cursor.gotoxy({ boardIndent, 0 });
	std::cout << wall.upLeftC;

	for (int i = 0; i < size; i++)
	{
		std::cout << wall.hor << wall.hor;
	}

	std::cout << wall.upRightC << std::endl;
}

void DrawLastLine(int size)
{
	CUR cursor;
	WALLS wall;

	cursor.gotoxy({ boardIndent, maxY + 1 });
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

void PlaceObjects(GAMEDATA& gData)
{
	switch (gData.curObj)
	{
	case OBJS::None:
		break;

	case OBJS::T:
		gData.obj.t.Place();
		break;

	case OBJS::Square:
		gData.obj.square.Place();
		break;

	case OBJS::Stick:
		gData.obj.stick.Place();
		break;

	case OBJS::LLeft:
		gData.obj.lLeft.Place();
		break;

	case OBJS::LRight:
		gData.obj.lRight.Place();
		break;

	case OBJS::ZLeft:
		gData.obj.zLeft.Place();
		break;

	case OBJS::ZRight:
		gData.obj.zRight.Place();
		break;

	default:
		break;
	}

	DrawNextObject(gData);
}

void SetNewSpeed(GAMEDATA& gData, TIME gTime)
{
	int speedUpTime = 10;

	DrawTime(gTime.secsElapsed);

	if (gData.frameRate < 10)
		gData.frameRate = gTime.secsElapsed / speedUpTime + 1;
}

void CheckOverlaps(GAMEDATA& gData)
{
	switch (gData.curObj)
	{
	case OBJS::None:
		break;

	case OBJS::T:
		gData.obj.t.CheckOverlapedCell(gData.board);
		break;

	case OBJS::Square:
		break;

	case OBJS::Stick:
		gData.obj.stick.CheckOverlapedCell(gData.board);
		break;

	case OBJS::LLeft:
		gData.obj.lLeft.CheckOverlapedCell(gData.board);
		break;

	case OBJS::LRight:
		gData.obj.lRight.CheckOverlapedCell(gData.board);
		break;

	case OBJS::ZLeft:
		gData.obj.zLeft.CheckOverlapedCell(gData.board);
		break;

	case OBJS::ZRight:
		gData.obj.zRight.CheckOverlapedCell(gData.board);
		break;

	default:
		break;
	}
}

void DrawScore(int score)
{
	CUR cursor;
	COORDS scoreCounterPos = { 45, 3 };

	cursor.gotoxy(scoreCounterPos);
	std::cout << "Score: " << score << "    ";

	cursor.gotoxy(txtPos);
}

void DrawTime(int time)
{
	CUR cursor;
	COORDS timeCounterPos = { 45, 2 };

	cursor.gotoxy(timeCounterPos);
	std::cout << "Time: " << time << "    ";

	cursor.gotoxy(txtPos);
}

void DrawLevel(GAMEDATA gData)
{
	CUR cursor;

	cursor.gotoxy({ 45, 1 });
	SetColor((COLORS)gData.frameRate);

	std::cout << "LEVEL: " << gData.frameRate;
	SetColor(defColor);
}

void DrawOnBoard(std::string text, int score)
{
	CUR curPos;
	short startPopupPosY = 10;
	const short startPopupPosX = 42;
	const short contiguos = 1;
	const int lineLength = 29;
	const short textStart = 4;
	const short textLength = 28;
	const int lineQty = 4;

	WALLS wall;					 // Cell Walls 

	curPos.gotoxy({ startPopupPosX, startPopupPosY });

	SetColor(WhiteOnPurple);
	std::cout << " " << wall.upLeftC;
	for (int i = 0; i < lineLength; i++)
	{
		std::cout << wall.hor;
	}
	std::cout << wall.upRightC << " ";

	int finishLine[3] = { -1, -1, -1 };

	char line[lineQty][lineLength];

	for (int j = 0; j < lineQty; j++)
	{
		for (int i = 0; i < lineLength; i++)
		{
			line[j][i] = ' ';
		}
	}

	for (int i = lineLength; i >= 0; i--)
	{
		if (i <= text.length())
		{
			if (text[i] == ' ')
			{
				finishLine[0] = i;
				break;
			}
		}
	}

	for (int i = lineLength + finishLine[0] - 1; i >= finishLine[0]; i--)
	{
		if (i <= text.length())
		{
			if (text[i] == ' ')
			{
				finishLine[1] = i;
				break;
			}
		}
	}

	for (int i = lineLength + finishLine[1] - 1; i >= finishLine[1]; i--)
	{
		if (i <= text.length())
		{
			if (text[i] == ' ')
			{
				finishLine[2] = i;
				break;
			}
		}
	}

	for (int i = 0; i < text.length(); i++)
	{
		if (i > finishLine[2] && text.length() > finishLine[1] + lineLength)
		{
			line[3][i - finishLine[2] - 1] = text[i];
		}
		else if (i > finishLine[1] && text.length() > finishLine[0] + lineLength)
		{
			line[2][i - finishLine[1] - 1] = text[i];
		}
		else if (i > finishLine[0] && text.length() > lineLength)
		{
			line[1][i - finishLine[0] - 1] = text[i];
		}
		else
		{
			line[0][i] = text[i];
		}
	}

	for (int i = 0; i < lineQty; i++)
	{
		curPos.gotoxy({ startPopupPosX, (startPopupPosY + i + contiguos) });
		std::cout << " " << wall.ver;
		SetColor(BlackOnPurple);
		for (int pos = 0; pos < lineLength; pos++)
		{
			std::cout << line[i][pos];
		}
		SetColor(WhiteOnPurple);
		std::cout << wall.ver << " ";
	}
	curPos.gotoxy({ startPopupPosX + contiguos * 2, (startPopupPosY + 3) });
	SetColor(BlackOnPurple);
	std::cout << "         SCORE: " << score;
	SetColor(WhiteOnPurple);


	curPos.gotoxy({ startPopupPosX, (startPopupPosY + lineQty + contiguos) });

	std::cout << " " << wall.lowLeftC;
	for (int i = 0; i < lineLength; i++)
	{
		std::cout << wall.hor;
	}
	std::cout << wall.lowRightC << " ";

	SetColor(WhiteOnBlack);
	curPos.gotoxy(txtPos);
	system("pause");
}