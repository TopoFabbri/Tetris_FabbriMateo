#pragma once

#include "ConioMenus.h"
#include "Globals.h"
#include <time.h>

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
void Settings(char input[]);