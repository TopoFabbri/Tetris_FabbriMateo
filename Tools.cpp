#include "Globals.h"

void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void SetFontSize(int size)
{
    static CONSOLE_FONT_INFOEX  fontex;
    fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetCurrentConsoleFontEx(hOut, 0, &fontex);
    fontex.FontWeight = 500;
    fontex.dwFontSize.X = size;
    fontex.dwFontSize.Y = size;
    SetCurrentConsoleFontEx(hOut, NULL, &fontex);
}

void DrawBox(COORDS size, COORDS pos, bool fill)
{
	CUR cursor;
	WALLS wall;

	// Draw top line
	cursor.gotoxy(pos);
	std::cout << wall.upLeftC;
	for (int i = 0; i < size.x; i++)
	{
		std::cout << wall.hor;
	}
	std::cout << wall.upRightC;
	pos.y++;

	// Draw side borders
	for (int y = 0; y < size.y; y++)
	{
		cursor.gotoxy(pos);
		std::cout << wall.ver;
		if (fill)
		{
			for (int i = 0; i < size.x; i++)
			{
				std::cout << " ";
			}
		}
		else
		{
			cursor.gotoxy({ pos.x + size.x + 1, pos.y });
		}
		std::cout << wall.ver;
		pos.y++;
	}

	// Draw last line
	cursor.gotoxy(pos);
	std::cout << wall.lowLeftC;
	for (int i = 0; i < size.x; i++)
	{
		std::cout << wall.hor;
	}
	std::cout << wall.lowRightC;
	pos.y++;
}

void DrawBox(COORDS size, COORDS pos, bool fill, std::string title)
{
	CUR cursor;
	WALLS wall;

	// Draw top walls
	cursor.gotoxy(pos);
	std::cout << wall.upLeftC;
	for (int i = 0; i < size.x; i++)
	{
		std::cout << wall.hor;
	}
	std::cout << wall.upRightC;
	pos.y++;

	// Draw indent
	cursor.gotoxy(pos);
	std::cout << wall.ver;
	for (int i = 0; i < ((size.x - title.length()) / 2); i++)
	{
		std::cout << " ";
	}

	std::cout << title;

	for (int i = 0; i < ((size.x - title.length()) / 2); i++)
	{
		std::cout << " ";
	}
	std::cout << wall.ver;
	pos.y++;

	// Draw division walls
	cursor.gotoxy(pos);
	std::cout << wall.leftT;
	for (int i = 0; i < size.x; i++)
	{
		std::cout << wall.hor;
	}
	std::cout << wall.rightT;
	pos.y++;

	// Draw side borders
	for (int y = 0; y < size.y; y++)
	{
		cursor.gotoxy(pos);
		std::cout << wall.ver;
		if (fill)
		{
			for (int i = 0; i < size.x; i++)
			{
				std::cout << " ";
			}
		}
		else
		{
			cursor.gotoxy({ pos.x + size.x + 1, pos.y });
		}
		std::cout << wall.ver;
		pos.y++;
	}

	// Draw last line
	cursor.gotoxy(pos);
	std::cout << wall.lowLeftC;
	for (int i = 0; i < size.x; i++)
	{
		std::cout << wall.hor;
	}
	std::cout << wall.lowRightC;
	pos.y++;
}

void SetColor(COLORS color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

COORDS ConLoc(COORDS boardLoc)
{
    boardLoc.x = boardLoc.x * 2 + 1 + boardIndent;
    boardLoc.y = boardLoc.y + 1;

    return boardLoc;
}

COLORS GetRandomColor()
{
	int color = rand() % 7;

	switch (color)
	{
	case 0:
		return BlackOnPurple;

	case 1:
		return BlackOnYellow;

	case 2:
		return BlackOnCyan;

	case 3:
		return BlackOnOrange;

	case 4:
		return BlackOnBlue;

	case 5:
		return BlackOnRed;

	case 6:
		return BlackOnGreen;

	default:
		break;
	}

	return defColor;
}