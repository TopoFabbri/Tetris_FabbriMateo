#include <iostream>
#include <Windows.h>
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
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    SetConsoleTitle(L"Tetris(?)");
    system("color 07");
    hidecursor();
    SetFontSize(22);
}

void Game()
{
    Menu();
}