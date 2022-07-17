#include <iostream>
#include <Windows.h>
#include "Menu.h"

void RunProgram();
void Defaults();
void Game();
void hidecursor();

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
}

void Game()
{
    Menu();
}

void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}