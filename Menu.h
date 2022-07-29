#pragma once

#include "ConioMenus.h"
#include "Globals.h"
#include "Game.h"

struct CREDS
{
	COORDS squarePos[4][2];
	COORDS velocity;
	COLORS squareColor[4][2];
	char text1[4]{ 'T', 'O', 'P', 'O' };
	std::string text2[4] = { "  ", "TE", "TR", "IS" };

	void DrawSquare(COORDS square, int x, int y)
	{
		CUR cur;
		cur.gotoxy(squarePos[x][y]);
		SetColor(squareColor[x][y]);

		if (y == 0)
			std::cout << text1[x] << " ";
		else
			std::cout << text2[x];

		SetColor(defColor);
	}

	void Move()
	{
		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				CUR cur;
				cur.gotoxy(squarePos[x][y]);
				SetColor(defColor);
				std::cout << "  ";
			}
		}

		for (int y = 0; y < 2; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				squarePos[x][y].x += velocity.x;
				squarePos[x][y].y += velocity.y;
				DrawSquare(squarePos[x][y], x, y);
			}
		}
	}
};

enum class MENUOPS
{
	Quit,
	Play,
	Credits,
	Settings,
	Menu
};

void Menu();
void Credits(char input[]);
void Settings(char input[], GAMEDATA& gData);
void PrintSettings(GAMEDATA& gData);
void ChangeSkinsMenu(GAMEDATA& gData, char input[]);
void ChangeSkin(GAMEDATA& gData, char input[]);
void SetKeys(char input[]);
void CheckCollide(CREDS& creds, COORDS boardSize);