#include "Stick.h"

bool Stick::DownCollideCell(CELL board[maxX][maxY], COORDS cell)
{
	return (board[cell.x][cell.y + 1].state == CELLSTATE::Static || cell.y >= maxY - 1);
}

bool Stick::LeftCollideCell(CELL board[maxX][maxY], COORDS cell)
{
	return (board[cell.x - 1][cell.y].state == CELLSTATE::Static || cell.x <= 0);
}

bool Stick::RightCollideCell(CELL board[maxX][maxY], COORDS cell)
{
	return (board[cell.x + 1][cell.y].state == CELLSTATE::Static || cell.x >= maxX - 1);
}

void Stick::SetRotation()
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

void Stick::RotationUp()
{
	left = { centerLeft.x - 1, centerLeft.y };
	centerRight = { centerLeft.x + 1, centerLeft.y };
	right = { centerLeft.x + 2, centerLeft.y };
}

void Stick::RotationRight()
{
	left = { centerLeft.x, centerLeft.y - 1 };
	centerRight = { centerLeft.x, centerLeft.y + 1 };
	right = { centerLeft.x, centerLeft.y + 2 };
}

void Stick::RotationLeft()
{
	left = { centerLeft.x, centerLeft.y + 1 };
	centerRight = { centerLeft.x, centerLeft.y - 1 };
	right = { centerLeft.x, centerLeft.y - 2 };
}

void Stick::RotationDown()
{
	left = { centerLeft.x + 1, centerLeft.y };
	centerRight = { centerLeft.x - 1, centerLeft.y };
	right = { centerLeft.x - 2, centerLeft.y };
}

void Stick::Kick()
{
	if (left.x >= maxX - 1 || right.x >= maxX - 1 || centerRight.x >= maxX - 1)
	{
		MoveLeft();
	}
	else if (left.x <= 0 || right.x <= 0 || centerRight.x <= 0)
	{
		MoveRight();
	}

	if (left.x >= maxX - 1 || right.x >= maxX - 1 || centerRight.x >= maxX - 1)
	{
		MoveLeft();
	}
	else if (left.x <= 0 || right.x <= 0 || centerRight.x <= 0)
	{
		MoveRight();
	}
}

COLDIR Stick::GetCollisions(CELL board[maxX][maxY])
{
	if (DownCollideCell(board, centerLeft) || DownCollideCell(board, left)
		|| DownCollideCell(board, right) || DownCollideCell(board, centerRight))
	{
		QuitFalling(board);
		return COLDIR::Down;
	}
	else if (LeftCollideCell(board, centerLeft) || LeftCollideCell(board, left)
		|| LeftCollideCell(board, right) || LeftCollideCell(board, centerRight))
	{
		return COLDIR::Left;
	}
	else if (RightCollideCell(board, centerLeft) || RightCollideCell(board, left)
		|| RightCollideCell(board, right) || RightCollideCell(board, centerRight))
	{
		return COLDIR::Right;
	}

	return COLDIR::None;
}

void Stick::Draw()
{
	CUR cursor;

	SetColor(color);

	cursor.gotoxy(ConLoc(centerLeft));
	std::cout << "  ";

	cursor.gotoxy(ConLoc(left));
	std::cout << "  ";

	cursor.gotoxy(ConLoc(right));
	std::cout << "  ";

	cursor.gotoxy(ConLoc(centerRight));
	std::cout << "  ";

	SetColor(defColor);
	cursor.gotoxy(txtPos);
}

void Stick::Place()
{
	current = true;

	centerLeft = initPiecePos;
	left = { centerLeft.x - 1, centerLeft.y };
	centerRight = { centerLeft.x + 1, centerLeft.y };
	right = { centerLeft.x + 2, centerLeft.y };

	rot = ROT::Up;
	SetRotation();
}

void Stick::QuitFalling(CELL board[maxX][maxY])
{
	board[centerLeft.x][centerLeft.y].color = color;
	board[centerLeft.x][centerLeft.y].state = CELLSTATE::Static;

	board[left.x][left.y].color = color;
	board[left.x][left.y].state = CELLSTATE::Static;

	board[right.x][right.y].color = color;
	board[right.x][right.y].state = CELLSTATE::Static;

	board[centerRight.x][centerRight.y].color = color;
	board[centerRight.x][centerRight.y].state = CELLSTATE::Static;

	current = false;
}

void Stick::FallOne()
{
	centerLeft.y++;
	left.y++;
	right.y++;
	centerRight.y++;
}

void Stick::MoveRight()
{
	centerLeft.x++;
	left.x++;
	right.x++;
	centerRight.x++;
}

void Stick::MoveLeft()
{
	centerLeft.x--;
	left.x--;
	right.x--;
	centerRight.x--;
}

void Stick::RotateRight()
{
	if (rot != ROT::Left)
		rot = (ROT)((int)rot + 1);
	else
		rot = ROT::Up;

	SetRotation();
	Kick();
}

void Stick::RotateLeft()
{
	if (rot != ROT::Up)
		rot = (ROT)((int)rot - 1);
	else
		rot = ROT::Left;

	SetRotation();
	Kick();
}