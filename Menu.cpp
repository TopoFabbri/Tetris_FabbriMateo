#include "Menu.h"

void Menu()
{
	MENUOPS Nav = MENUOPS::Menu;

	char input[20] = { 'w', 'a', 's', 'd', '1', '0', '4', '6', ' ' };
	char buttonTxt[txtMaxLength][maxButtons]
	{
		{' ', ' ', ' ', 'P', 'L', 'A', 'Y', ' ', ' ', ' '},
		{' ', 'C', 'R', 'E', 'D', 'I', 'T', 'S', ' ', ' '},
		{' ', 'S', 'E', 'T', 'T', 'I', 'N', 'G', 'S', ' '},
	};

	int selector = 0;

	do
	{
		switch (Nav)
		{
		case MENUOPS::Quit:
			break;

		case MENUOPS::Play:
			Play(input);
			Nav = MENUOPS::Menu;
			break;

		case MENUOPS::Credits:
			Credits(input);
			Nav = MENUOPS::Menu;
			break;

		case MENUOPS::Settings:
			Settings(input);
			Nav = MENUOPS::Menu;
			break;

		case MENUOPS::Menu:
			system("cls");
			PrintTitle("MENU");
			MenuNavigator(3, buttonTxt, input, selector);

			Nav = (MENUOPS)selector;
			break;

		default:
			break;
		}

	} while (Nav != MENUOPS::Quit);
}

void Credits(char input[])
{
	system("cls");
	COORDS boxSize{ 115, 25 };
	COORDS initPos{ 50, 15 };
	CREDS creds;
	char key = ' ';

	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			creds.squarePos[x][y] = { initPos.x + x * 2, initPos.y + y };
			creds.squareColor[x][y] = (y == 0 ? WhiteOnBlue : WhiteOnOrange);
		}
	}

	creds.squareColor[0][1] = WhiteOnBlue;
	creds.squareColor[3][0] = WhiteOnOrange;

	do
	{
		creds.velocity = { ((rand() % 1 - 2) * 2), (rand() % 2 - 1) };

	} while (creds.velocity.x == 0 || creds.velocity.y == 0);

	DrawBox(boxSize, { 0, 0 }, true);

	do
	{
		CheckCollide(creds, boxSize);

		if (clock() % 150 == 0)
			creds.Move();

		if (_kbhit())
			key = _getch();

	} while (key != input[(int)KEYS::Back]);
}

void CheckCollide(CREDS& creds, COORDS boardSize)
{
	if (creds.squarePos[0][0].x <= 2)
	{
		creds.velocity.x = 2;
	}

	if (creds.squarePos[0][0].y <= 1)
	{
		creds.velocity.y = 1;
	}

	if (creds.squarePos[3][1].x >= boardSize.x - 2)
	{
		creds.velocity.x = -2;
	}

	if (creds.squarePos[3][1].y >= boardSize.y)
	{
		creds.velocity.y = -1;
	}
}

void Settings(char input[])
{
	system("cls");

	char btnTxt[txtMaxLength][maxButtons]
	{
		{' ', ' ', ' ', 'K', 'E', 'Y', 'S', ' ', ' ', ' '},
	};
	int selector;

	do
	{
		PrintTitle("SETTINGS");
		MenuNavigator(1, btnTxt, input, selector);

		if (selector == 1)
			SetKeys(input);

	} while (selector != 0);
}

void SetKeys(char input[])
{
	CUR cur;
	char in;

	system("cls");

	do
	{
		cur.gotoxy({ 0, 0 });

		PrintTitle("KEYS");

		std::cout << std::endl;


		SetColor(BlueOnBlack);
		std::cout << "1: Up (" << input[(int)KEYS::Up] << ")" << std::endl;

		SetColor(GreenOnBlack);
		std::cout << "2: Left (" << input[(int)KEYS::Left] << ")" << std::endl;

		SetColor(RedOnBlack);
		std::cout << "3: Down (" << input[(int)KEYS::Down] << ")" << std::endl;

		SetColor(PurpleOnBlack);
		std::cout << "4: Right (" << input[(int)KEYS::Right] << ")" << std::endl;

		SetColor(YellowOnBlack);
		std::cout << "5: Enter (" << input[(int)KEYS::Enter] << ")" << std::endl;

		SetColor(GrayOnBlack);
		std::cout << "6: Back (" << input[(int)KEYS::Back] << ")" << std::endl;

		SetColor(CyanOnBlack);
		std::cout << "7: Rotate Left (" << input[(int)KEYS::RotateL] << ")" << std::endl;

		SetColor(OrangeOnBlack);
		std::cout << "8: Rotate Right (" << input[(int)KEYS::RotateR] << ")" << std::endl;

		SetColor(WhiteOnBlack);
		std::cout << "9: Drop Down (" << input[(int)KEYS::DropDown] << ")" << std::endl << std::endl;

		std::cout << input[(int)KEYS::Back] << ": Go Back" << std::endl << std::endl;
		SetColor(defColor);
		in = _getch();

		switch (in)
		{
		case '1':
			std::cout << "Select a new key for 'Up'";
			input[(int)KEYS::Up] = _getch();
			system("cls");
			break;

		case '2':
			std::cout << "Select a new key for 'Left'";
			input[(int)KEYS::Left] = _getch();
			system("cls");
			break;

		case '3':
			std::cout << "Select a new key for 'Down'";
			input[(int)KEYS::Down] = _getch();
			system("cls");
			break;

		case '4':
			std::cout << "Select a new key for 'Right'";
			input[(int)KEYS::Right] = _getch();
			system("cls");
			break;

		case '5':
			std::cout << "Select a new key for 'Enter'";
			input[(int)KEYS::Enter] = _getch();
			system("cls");
			break;

		case '6':
			std::cout << "Select a new key for 'Back'";
			input[(int)KEYS::Back] = _getch();
			system("cls");
			break;

		case '7':
			std::cout << "Select a new key for 'Rotate Left'";
			input[(int)KEYS::RotateL] = _getch();
			system("cls");
			break;

		case '8':
			std::cout << "Select a new key for 'Rotate Right'";
			input[(int)KEYS::RotateR] = _getch();
			system("cls");
			break;

		case '9':
			std::cout << "Select a new key for 'Drop Down'";
			input[(int)KEYS::DropDown] = _getch();
			system("cls");
			break;

		default:
			break;
		}
	} while (in != input[(int)KEYS::Back]);

	system("cls");
}