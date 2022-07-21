#include "ConioMenus.h"

void MenuNavigator(const int opsQty, char text[10][10], char input[], int& options)
{
	CUR conCursor;
	const int maxOps = 10;
	int cursor = 0;
	bool chose = false;
	int saveIn;

	do
	{
		COORDS controlsPos{ 2, 22 };
		for (int ops = 0; ops < opsQty; ops++)
		{
			PrintOptions(text, ops, cursor);
		}

		SetColor(WhiteOnBlack);

		conCursor.gotoxy(controlsPos);
		std::cout << input[(int)KEYS::Left] << ": Move Left";
		controlsPos.y++;

		conCursor.gotoxy(controlsPos);
		std::cout << input[(int)KEYS::Right] << ": Move Right";
		controlsPos.y++;

		conCursor.gotoxy(controlsPos);
		std::cout << input[(int)KEYS::Enter] << ": Select";
		controlsPos.y += 2;

		conCursor.gotoxy(controlsPos);
		std::cout << input[(int)KEYS::Back] << ": Back";

		saveIn = GetMenuInput(cursor, input, opsQty);
		chose = (saveIn != 0);
	} while (!chose);

	if (saveIn == 1)
	{
		options = cursor + 1;
	}
	else if (saveIn == 2)
	{
		options = 0;
	}
}

int GetMenuInput(int& cursor, char input[], int opsQty)
{
	if (!_kbhit())
	{
		return 0;
	}

	char key = _getch();

	if (key == input[(int)KEYS::Left])
	{
		if (cursor > 0)
			cursor--;
		else
			cursor = opsQty - 1;
	}
	else if (key == input[(int)KEYS::Right])
	{
		if (cursor < opsQty - 1)
			cursor++;
		else
			cursor = 0;
	}
	else if (key == input[(int)KEYS::Enter])
	{
		return 1;
	}
	else if (key == input[(int)KEYS::Back])
	{
		return 2;
	}

	return 0;
}

void PrintOptions(char displayText[10][10], int ops, int cursor)
{
	WALLS wall;

	const short boxLength = 15;
	const int boxSpace = 10;
	int line[3] = { 5, 6, 7 };

	if (ops == cursor)
		SetColor(PurpleOnBlack);
	else
		SetColor(BlackOnBlack);

	COORD curPos = { boxLength * ops, (short)line[0] };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), curPos);
	std::cout << wall.upLeftC;
	for (int i = 0; i < boxSpace; i++)
	{
		std::cout << wall.hor;
	}
	std::cout << wall.upRightC;

	curPos = { (short)(boxLength * ops), (short)line[1] };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), curPos);
	std::cout << wall.ver;
	for (int i = 0; i < boxSpace; i++)
	{
		std::cout << displayText[ops][i];
	}
	std::cout << wall.ver;

	curPos = { (short)(boxLength * ops), (short)line[2] };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), curPos);
	std::cout << wall.lowLeftC;
	for (int i = 0; i < boxSpace; i++)
	{
		std::cout << wall.hor;
	}
	std::cout << wall.lowRightC;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WhiteOnBlack);

	std::cout << std::endl << std::endl;
}

void PrintTitle(std::string title)
{
	const int splashLength = 120;
	int titleLength = title.length();
	CUR conCursor;

	conCursor.gotoxy({ 0, 0 });

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BlackOnWhite);
	for (int i = 0; i <= splashLength; i++)
	{
		std::cout << " ";
	}
	std::cout << std::endl;

	for (int i = 0; i < splashLength / 2 - (titleLength * 2 - 1) / 2; i++)
	{
		std::cout << " ";
	}

	for (int i = 0; i < titleLength; i++)
	{
		if (i > 0)
			std::cout << " ";

		std::cout << title[i];
	}

	for (int i = 0; i < splashLength / 2 - (titleLength * 2 - 1) / 2; i++)
	{
		std::cout << " ";
	}
	std::cout << std::endl;

	for (int i = 0; i <= splashLength; i++)
	{
		std::cout << " ";
	}
	std::cout << std::endl;

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WhiteOnBlack);
}