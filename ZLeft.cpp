#include "ZLeft.h"

bool ZLeft::DownCollideCell(CELL board[maxX][maxY], COORDS cell)
{
	return (board[cell.x][cell.y + 1].state == CELLSTATE::Static || cell.y >= maxY - 1);
}

bool ZLeft::LeftCollideCell(CELL board[maxX][maxY], COORDS cell)
{
	return (board[cell.x - 1][cell.y].state == CELLSTATE::Static || cell.x <= 0);
}

bool ZLeft::RightCollideCell(CELL board[maxX][maxY], COORDS cell)
{
	return (board[cell.x + 1][cell.y].state == CELLSTATE::Static || cell.x >= maxX - 1);
}

void ZLeft::SetRotation()
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

void ZLeft::RotationUp()
{
	left = { center.x - 1, center.y };
	downRight = { center.x + 1, center.y + 1 };
	down = { center.x, center.y + 1 };
}

void ZLeft::RotationRight()
{
	left = { center.x, center.y - 1 };
	downRight = { center.x - 1, center.y + 1 };
	down = { center.x - 1, center.y };
}

void ZLeft::RotationLeft()
{
	left = { center.x, center.y + 1 };
	downRight = { center.x + 1, center.y - 1 };
	down = { center.x + 1, center.y };
}

void ZLeft::RotationDown()
{
	left = { center.x + 1, center.y };
	downRight = { center.x - 1, center.y - 1 };
	down = { center.x, center.y - 1 };
}

void ZLeft::Kick()
{
	if (left.x >= maxX - 1 || downRight.x >= maxX - 1 || down.x >= maxX - 1)
	{
		MoveLeft();
	}
	else if (left.x <= 0 || downRight.x <= 0 || down.x <= 0)
	{
		MoveRight();
	}
}

COLDIR ZLeft::GetCollisions(CELL board[maxX][maxY])
{
	if (DownCollideCell(board, center) || DownCollideCell(board, left)
		|| DownCollideCell(board, downRight) || DownCollideCell(board, down))
	{
		QuitFalling(board);
		return COLDIR::Down;
	}
	else if (LeftCollideCell(board, center) || LeftCollideCell(board, left)
		|| LeftCollideCell(board, downRight) || LeftCollideCell(board, down))
	{
		return COLDIR::Left;
	}
	else if (RightCollideCell(board, center) || RightCollideCell(board, left)
		|| RightCollideCell(board, downRight) || RightCollideCell(board, down))
	{
		return COLDIR::Right;
	}

	return COLDIR::None;
}

void ZLeft::Draw()
{
	CUR cursor;

	SetColor(color);

	cursor.gotoxy(ConLoc(center));
	std::cout << "  ";

	cursor.gotoxy(ConLoc(left));
	std::cout << "  ";

	cursor.gotoxy(ConLoc(downRight));
	std::cout << "  ";

	cursor.gotoxy(ConLoc(down));
	std::cout << "  ";

	SetColor(defColor);
	cursor.gotoxy(txtPos);
}

void ZLeft::Place()
{
	current = true;

	center = initPiecePos;
	left = { center.x - 1, center.y };
	downRight = { center.x + 1, center.y };
	down = { center.x, center.y + 1 };

	rot = ROT::Up;
	SetRotation();
}

void ZLeft::QuitFalling(CELL board[maxX][maxY])
{
	board[center.x][center.y].color = color;
	board[center.x][center.y].state = CELLSTATE::Static;

	board[left.x][left.y].color = color;
	board[left.x][left.y].state = CELLSTATE::Static;

	board[downRight.x][downRight.y].color = color;
	board[downRight.x][downRight.y].state = CELLSTATE::Static;

	board[down.x][down.y].color = color;
	board[down.x][down.y].state = CELLSTATE::Static;

	current = false;
}

void ZLeft::FallOne()
{
	center.y++;
	left.y++;
	downRight.y++;
	down.y++;
}

void ZLeft::MoveRight()
{
	center.x++;
	left.x++;
	downRight.x++;
	down.x++;
}

void ZLeft::MoveLeft()
{
	center.x--;
	left.x--;
	downRight.x--;
	down.x--;
}

void ZLeft::RotateRight()
{
	if (rot != ROT::Left)
		rot = (ROT)((int)rot + 1);
	else
		rot = ROT::Up;

	SetRotation();
	Kick();
}

void ZLeft::RotateLeft()
{
	if (rot != ROT::Up)
		rot = (ROT)((int)rot - 1);
	else
		rot = ROT::Left;

	SetRotation();
	Kick();
}