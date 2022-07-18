#include "T.h"

COLDIR T::GetCollisions(CELL board[maxX][maxY])
{
	if (DownCollideCell(board, center) || DownCollideCell(board, left)
		|| DownCollideCell(board, right) || DownCollideCell(board, down))
	{
		QuitFalling(board);
		return COLDIR::Down;
	}
	else if (LeftCollideCell(board, center) || LeftCollideCell(board, left)
		|| LeftCollideCell(board, right) || LeftCollideCell(board, down))
	{
		return COLDIR::Left;
	}
	else if (RightCollideCell(board, center) || RightCollideCell(board, left)
		|| RightCollideCell(board, right) || RightCollideCell(board, down))
	{
		return COLDIR::Right;
	}

	return COLDIR::None;
}

bool T::DownCollideCell(CELL board[maxX][maxY], COORDS cell)
{
	return (board[cell.x][cell.y + 1].state == CELLSTATE::Static || cell.y >= maxY - 1);
}

bool T::LeftCollideCell(CELL board[maxX][maxY], COORDS cell)
{
	return (board[cell.x - 1][cell.y].state == CELLSTATE::Static || cell.x <= 0);
}

bool T::RightCollideCell(CELL board[maxX][maxY], COORDS cell)
{
	return (board[cell.x + 1][cell.y].state == CELLSTATE::Static || cell.x >= maxX - 1);
}

void T::SetRotation()
{
	switch (rot)
	{
	case ROT::Up:
		RotationUp();
		break;

	case ROT::Right:
		RotationRight();
		break;

	case ROT::Down:
		RotationDown();
		break;

	case ROT::Left:
		RotationLeft();
		break;

	default:
		break;
	}
}

void T::RotationUp()
{
	left = { center.x - 1, center.y };
	right = { center.x + 1, center.y };
	down = { center.x, center.y + 1 };
}

void T::RotationRight()
{
	left = { center.x, center.y - 1 };
	right = { center.x, center.y + 1 };
	down = { center.x - 1, center.y };
}

void T::RotationLeft()
{
	left = { center.x, center.y + 1 };
	right = { center.x, center.y - 1 };
	down = { center.x + 1, center.y };
}

void T::RotationDown()
{
	left = { center.x + 1, center.y };
	right = { center.x - 1, center.y };
	down = { center.x, center.y - 1 };
}

void T::Kick()
{
	if (left.x >= maxX - 1 || right.x >= maxX - 1 || down.x >= maxX - 1)
	{
		MoveLeft();
	}
	else if (left.x <= 0 || right.x <= 0 || down.x <= 0)
	{
		MoveRight();
	}
}

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

void T::Place()
{
	current = true;
	
	center = initPiecePos;
	left = { center.x - 1, center.y };
	right = { center.x + 1, center.y };
	down = { center.x, center.y + 1 };

	rot = ROT::Up;
	SetRotation();
}

void T::QuitFalling(CELL board[maxX][maxY])
{
	board[center.x][center.y].color = color;
	board[center.x][center.y].state = CELLSTATE::Static;

	board[left.x][left.y].color = color;
	board[left.x][left.y].state = CELLSTATE::Static;

	board[right.x][right.y].color = color;
	board[right.x][right.y].state = CELLSTATE::Static;

	board[down.x][down.y].color = color;
	board[down.x][down.y].state = CELLSTATE::Static;

	current = false;
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
	if (rot != ROT::Left)
		rot = (ROT)((int)rot + 1);
	else
		rot = ROT::Up;

	SetRotation();
	Kick();
}

void T::RotateLeft()
{
	if (rot != ROT::Up)
		rot = (ROT)((int)rot - 1);
	else
		rot = ROT::Left;

	SetRotation();
	Kick();
}