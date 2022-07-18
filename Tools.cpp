#include "Globals.h"

void hidecursor()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void SetFontSize(int size)
{
    static CONSOLE_FONT_INFOEX  fontex;
    fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetCurrentConsoleFontEx(hOut, 0, &fontex);
    fontex.FontWeight = 500;
    fontex.dwFontSize.X = size;
    fontex.dwFontSize.Y = size;
    SetCurrentConsoleFontEx(hOut, NULL, &fontex);
}

void SetColor(COLORS color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

COORDS ConLoc(COORDS boardLoc)
{
    boardLoc.x = boardLoc.x * 2 + 1;
    boardLoc.y = boardLoc.y + 1;

    return boardLoc;
}