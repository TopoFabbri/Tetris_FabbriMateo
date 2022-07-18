#include "T.h"

void T::Draw()
{
	CUR cursor;

	SetColor(color);

	cursor.gotoxy(ConLoc(center));
	std::cout << "  ";

	cursor.gotoxy(ConLoc(left));
	std::cout << "  ";

	cursor.gotoxy(ConLoc(right));
	std::cout << "  ";

	cursor.gotoxy(ConLoc(down));
	std::cout << "  ";

	SetColor(defColor);
	cursor.gotoxy(txtPos);
}

void T::FallOne()
{
	center.y++;
	left.y++;
	right.y++;
	down.y++;
}

void T::MoveRight()
{
	center.x++;
	left.x++;
	right.x++;
	down.x++;
}

void T::MoveLeft()
{
	center.x--;
	left.x--;
	right.x--;
	down.x--;
}

void T::RotateRight()
{
}

void T::RotateLeft()
{
}

void T::DropDown()
{
}