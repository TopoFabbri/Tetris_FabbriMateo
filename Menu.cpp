#include "Menu.h"

void Menu()
{
	MENUOPS Nav = MENUOPS::Menu;

	char input[20] = { 'w', 'a', 's', 'd', '1', '0' };
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

	char btnTxt[txtMaxLength][maxButtons];
	int selector;

	PrintTitle("CREDITS");
	MenuNavigator(0, btnTxt, input, selector);
}

void Settings(char input[])
{
	system("cls");

	char btnTxt[txtMaxLength][maxButtons];
	int selector;

	PrintTitle("SETTINGS");
	MenuNavigator(0, btnTxt, input, selector);
}