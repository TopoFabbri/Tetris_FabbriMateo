#include <iostream>
#include <Windows.h>
#include <time.h>
#include <string>
#include "Menu.h"

void RunProgram();
void Defaults();
void Game();

void main()
{
    RunProgram();
}

void RunProgram()
{
    Defaults();
    Game();
}

void Defaults()
{
    srand(time(nullptr));
    SetFontSize(28, 28);
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    SetConsoleTitleW(L"Tetris");
    system("color 07");
    hidecursor();
}

void Game()
{
    Menu();
}