#pragma once

#include <Windows.h>
#include <iostream>
#include <conio.h>
#include "Globals.h"

void MenuNavigator(const int opsQty, char[10][10], char input[], int& options);
void PrintOptions(char displayText[10][10], int ops, int cursor);
int GetMenuInput(int& cursor, char input[], int opsQty);
void PrintTitle(std::string title);