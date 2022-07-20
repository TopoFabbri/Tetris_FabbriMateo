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
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    DrawFrames(L"Tetris(?)");
    system("color 07");
    hidecursor();
    SetFontSize(22);
}

void Game()
{
    Menu();
}