#include "Menu.h"

void Menu()
{
	MENUOPS Nav = MENUOPS::Menu;
	GAMEDATA gData{};

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
			Play(input, gData);
			Nav = MENUOPS::Menu;
			break;

		case MENUOPS::Credits:
			Credits(input);
			Nav = MENUOPS::Menu;
			break;

		case MENUOPS::Settings:
			Settings(input, gData);
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
	COORDS boxSize{ 109, 25 };
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
		COLORS newBlue;
		COLORS newOrange;
		creds.velocity.x = 2;

		do
		{
			newOrange = (COLORS)(rand() % 15 + 192);
		} while (newOrange == 204);

		do
		{
			newBlue = (COLORS)(rand() % 15 + 16);
		} while (newBlue == 17);

		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				if (creds.squareColor[x][y] <= 207 && creds.squareColor[x][y] >= 192)
				{
					creds.squareColor[x][y] = newOrange;
				}
				else
				{
					creds.squareColor[x][y] = newBlue;
				}
			}
		}
	}

	if (creds.squarePos[0][0].y <= 1)
	{
		COLORS newBlue;
		COLORS newOrange;
		creds.velocity.y = 1;

		do
		{
			newOrange = (COLORS)(rand() % 15 + 192);
		} while (newOrange == 204);

		do
		{
			newBlue = (COLORS)(rand() % 15 + 16);
		} while (newBlue == 17);

		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				if (creds.squareColor[x][y] <= 207 && creds.squareColor[x][y] >= 192)
				{
					creds.squareColor[x][y] = newOrange;
				}
				else
				{
					creds.squareColor[x][y] = newBlue;
				}
			}
		}
	}

	if (creds.squarePos[3][1].x >= boardSize.x - 2)
	{
		COLORS newBlue;
		COLORS newOrange;
		creds.velocity.x = -2;

		do
		{
			newOrange = (COLORS)(rand() % 15 + 192);
		} while (newOrange == 204);

		do
		{
			newBlue = (COLORS)(rand() % 15 + 16);
		} while (newBlue == 17);

		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				if (creds.squareColor[x][y] <= 207 && creds.squareColor[x][y] >= 192)
				{
					creds.squareColor[x][y] = newOrange;
				}
				else
				{
					creds.squareColor[x][y] = newBlue;
				}
			}
		}
	}

	if (creds.squarePos[3][1].y >= boardSize.y)
	{
		COLORS newBlue;
		COLORS newOrange;
		creds.velocity.y = -1;

		do
		{
			newOrange = (COLORS)(rand() % 15 + 192);
		} while (newOrange == 204);

		do
		{
			newBlue = (COLORS)(rand() % 15 + 16);
		} while (newBlue == 17);

		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				if (creds.squareColor[x][y] <= 207 && creds.squareColor[x][y] >= 192)
				{
					creds.squareColor[x][y] = newOrange;
				}
				else
				{
					creds.squareColor[x][y] = newBlue;
				}
			}
		}
	}
}

void Settings(char input[], GAMEDATA& gData)
{
	system("cls");

	char btnTxt[txtMaxLength][maxButtons]
	{
		{' ', ' ', ' ', 'K', 'E', 'Y', 'S', ' ', ' ', ' '},
		{' ', ' ', ' ', 'S', 'K', 'I', 'N', ' ', ' ', ' '},
	};
	int selector;

	do
	{
		PrintTitle("SETTINGS");
		MenuNavigator(2, btnTxt, input, selector);

		if (selector == 1)
			SetKeys(input);
		else if (selector == 2)
			ChangeSkinsMenu(gData, input);

	} while (selector != 0);
}

void ChangeSkinsMenu(GAMEDATA& gData, char input[])
{
	char in = ' ';
	system("cls");

	do
	{
		in = ' ';

		CUR cur{};
		cur.gotoxy({ 0, 0 });

		std::cout << "Select which figure to modify" << std::endl << std::endl
			<< input[(int)KEYS::Left] << ": Navigate left" << std::endl
			<< input[(int)KEYS::Right] << ": Navigate right" << std::endl
			<< input[(int)KEYS::Enter] << ": Select" << std::endl << std::endl
			<< input[(int)KEYS::Back] << ": Back" << std::endl;

		DrawObject(gData);

		if (_kbhit())
			in = _getch();

		if (in == input[(int)KEYS::Right])
		{
			if (gData.curObj == OBJS::ZRight)
				gData.curObj = OBJS::T;
			else
				gData.curObj = (OBJS)((int)gData.curObj + 1);

			system("cls");
		}
		else if (in == input[(int)KEYS::Left])
		{
			if (gData.curObj == OBJS::T)
				gData.curObj = OBJS::ZRight;
			else
				gData.curObj = (OBJS)((int)gData.curObj - 1);

			system("cls");
		}
		if (in == input[(int)KEYS::Enter])
		{
			ChangeSkin(gData, input);

			system("cls");
		}

	} while (in != input[(int)KEYS::Back]);

	system("cls");
}

void ChangeSkin(GAMEDATA& gData, char input[])
{
	char in;
	bool left = false;
	char btnTxt[10][10]
	{
		{' ', ' ', ' ', 'L', 'E', 'F', 'T', ' ', ' ', ' '},
		{' ', ' ', 'R', 'I', 'G', 'H', 'T', ' ', ' ', ' '},
	};
	int selector = 1;

	do
	{
		system("cls");

		MenuNavigator(2, btnTxt, input, selector);

		if (selector == 1)
			left = true;
		else if (selector == 2)
			left = false;
		else if (selector == 0)
			return;

		system("cls");

		do
		{
			in = ' ';
			if (_kbhit())
				in = _getch();

			DrawObject(gData);

			switch (gData.curObj)
			{
			case OBJS::None:
				break;

			case OBJS::T:
				if (left)
				{
					if (in == input[(int)KEYS::Left])
						gData.obj.t.lHalf -= 1;
					else if (in == input[(int)KEYS::Right])
						gData.obj.t.lHalf += 1;

					if (gData.obj.t.lHalf < 32)
						gData.obj.t.lHalf = 255;
					else if (gData.obj.t.lHalf > 255)
						gData.obj.t.lHalf = 32;
				}
				else
				{
					if (in == input[(int)KEYS::Left])
						gData.obj.t.rHalf -= 1;
					else if (in == input[(int)KEYS::Right])
						gData.obj.t.rHalf += 1;

					if (gData.obj.t.rHalf < 32)
						gData.obj.t.rHalf = 255;
					else if (gData.obj.t.rHalf > 255)
						gData.obj.t.rHalf = 32;
				}
				break;

			case OBJS::Square:
				if (left)
				{
					if (in == input[(int)KEYS::Left])
						gData.obj.square.lHalf -= 1;
					else if (in == input[(int)KEYS::Right])
						gData.obj.square.lHalf += 1;

					if (gData.obj.square.lHalf < 32)
						gData.obj.square.lHalf = 255;
					else if (gData.obj.square.lHalf > 255)
						gData.obj.square.lHalf = 32;
				}
				else
				{
					if (in == input[(int)KEYS::Left])
						gData.obj.square.rHalf -= 1;
					else if (in == input[(int)KEYS::Right])
						gData.obj.square.rHalf += 1;

					if (gData.obj.square.rHalf < 32)
						gData.obj.square.rHalf = 255;
					else if (gData.obj.square.rHalf > 255)
						gData.obj.square.rHalf = 32;
				}

				break;

			case OBJS::Stick:
				if (left)
				{
					if (in == input[(int)KEYS::Left])
						gData.obj.stick.lHalf -= 1;
					else if (in == input[(int)KEYS::Right])
						gData.obj.stick.lHalf += 1;

					if (gData.obj.stick.lHalf < 32)
						gData.obj.stick.lHalf = 255;
					else if (gData.obj.stick.lHalf > 255)
						gData.obj.stick.lHalf = 32;
				}
				else
				{
					if (in == input[(int)KEYS::Left])
						gData.obj.stick.rHalf -= 1;
					else if (in == input[(int)KEYS::Right])
						gData.obj.stick.rHalf += 1;

					if (gData.obj.stick.rHalf < 32)
						gData.obj.stick.rHalf = 255;
					else if (gData.obj.stick.rHalf > 255)
						gData.obj.stick.rHalf = 32;
				}

				break;

			case OBJS::LLeft:
				if (left)
				{
					if (in == input[(int)KEYS::Left])
						gData.obj.lLeft.lHalf -= 1;
					else if (in == input[(int)KEYS::Right])
						gData.obj.lLeft.lHalf += 1;

					if (gData.obj.lLeft.lHalf < 32)
						gData.obj.lLeft.lHalf = 255;
					else if (gData.obj.lLeft.lHalf > 255)
						gData.obj.lLeft.lHalf = 32;
				}
				else
				{
					if (in == input[(int)KEYS::Left])
						gData.obj.lLeft.rHalf -= 1;
					else if (in == input[(int)KEYS::Right])
						gData.obj.lLeft.rHalf += 1;

					if (gData.obj.lLeft.rHalf < 32)
						gData.obj.lLeft.rHalf = 255;
					else if (gData.obj.lLeft.rHalf > 255)
						gData.obj.lLeft.rHalf = 32;
				}

				break;

			case OBJS::LRight:
				if (left)
				{
					if (in == input[(int)KEYS::Left])
						gData.obj.lRight.lHalf -= 1;
					else if (in == input[(int)KEYS::Right])
						gData.obj.lRight.lHalf += 1;

					if (gData.obj.lRight.lHalf < 32)
						gData.obj.lRight.lHalf = 255;
					else if (gData.obj.lRight.lHalf > 255)
						gData.obj.lRight.lHalf = 32;
				}
				else
				{
					if (in == input[(int)KEYS::Left])
						gData.obj.lRight.rHalf -= 1;
					else if (in == input[(int)KEYS::Right])
						gData.obj.lRight.rHalf += 1;

					if (gData.obj.lRight.rHalf < 32)
						gData.obj.lRight.rHalf = 255;
					else if (gData.obj.lRight.rHalf > 255)
						gData.obj.lRight.rHalf = 32;
				}

				break;

			case OBJS::ZLeft:
				if (left)
				{
					if (in == input[(int)KEYS::Left])
						gData.obj.zLeft.lHalf -= 1;
					else if (in == input[(int)KEYS::Right])
						gData.obj.zLeft.lHalf += 1;

					if (gData.obj.zLeft.lHalf < 32)
						gData.obj.zLeft.lHalf = 255;
					else if (gData.obj.zLeft.lHalf > 255)
						gData.obj.zLeft.lHalf = 32;
				}
				else
				{
					if (in == input[(int)KEYS::Left])
						gData.obj.zLeft.rHalf -= 1;
					else if (in == input[(int)KEYS::Right])
						gData.obj.zLeft.rHalf += 1;

					if (gData.obj.zLeft.rHalf < 32)
						gData.obj.zLeft.rHalf = 255;
					else if (gData.obj.zLeft.rHalf > 255)
						gData.obj.zLeft.rHalf = 32;
				}

				break;

			case OBJS::ZRight:
				if (left)
				{
					if (in == input[(int)KEYS::Left])
						gData.obj.zRight.lHalf -= 1;
					else if (in == input[(int)KEYS::Right])
						gData.obj.zRight.lHalf += 1;

					if (gData.obj.zRight.lHalf < 32)
						gData.obj.zRight.lHalf = 255;
					else if (gData.obj.zRight.lHalf > 255)
						gData.obj.zRight.lHalf = 32;
				}
				else
				{
					if (in == input[(int)KEYS::Left])
						gData.obj.zRight.rHalf -= 1;
					else if (in == input[(int)KEYS::Right])
						gData.obj.zRight.rHalf += 1;

					if (gData.obj.zRight.rHalf < 32)
						gData.obj.zRight.rHalf = 255;
					else if (gData.obj.zRight.rHalf > 255)
						gData.obj.zRight.rHalf = 32;
				}

				break;

			default:;
			}
		} while (in != input[(int)KEYS::Back]);

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