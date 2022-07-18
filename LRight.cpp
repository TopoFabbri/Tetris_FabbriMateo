#include "LRight.h"

bool LRight::DownCollideCell(CELL board[maxX][maxY], COORDS cell)
{
	return (board[cell.x][cell.y + 1].state == CELLSTATE::Static || cell.y >= maxY - 1);
}

bool LRight::LeftCollideCell(CELL board[maxX][maxY], COORDS cell)
{
	return (board[cell.x - 1][cell.y].state == CELLSTATE::Static || cell.x <= 0);
}

bool LRight::RightCollideCell(CELL board[maxX][maxY], COORDS cell)
{
	return (board[cell.x + 1][cell.y].state == CELLSTATE::Static || cell.x >= maxX - 1);
}

void LRight::SetRotation()
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

void LRight::RotationUp()
{
	corner = { center.x - 1, center.y };
	right = { center.x + 1, center.y };
	down = { center.x - 1, center.y + 1 };
}

void LRight::RotationRight()
{
	corner = { center.x, center.y - 1 };
	right = { center.x, center.y + 1 };
	down = { center.x - 1, center.y - 1 };
}

void LRight::RotationLeft()
{
	corner = { center.x, center.y + 1 };
	right = { center.x, center.y - 1 };
	down = { center.x + 1, center.y + 1 };
}

void LRight::RotationDown()
{
	corner = { center.x + 1, center.y };
	right = { center.x - 1, center.y };
	down = { center.x + 1, center.y - 1 };
}

void LRight::Kick()
{
	if (corner.x >= maxX - 1 || right.x >= maxX - 1 || down.x >= maxX - 1)
	{
		MoveLeft();
	}
	else if (corner.x <= 0 || right.x <= 0 || down.x <= 0)
	{
		MoveRight();
	}
}

COLDIR LRight::GetCollisions(CELL board[maxX][maxY])
{
	if (DownCollideCell(board, center) || DownCollideCell(board, corner)
		|| DownCollideCell(board, right) || DownCollideCell(board, down))
	{
		QuitFalling(board);
		return COLDIR::Down;
	}
	else if (LeftCollideCell(board, center) || LeftCollideCell(board, corner)
		|| LeftCollideCell(board, right) || LeftCollideCell(board, down))
	{
		return COLDIR::Left;
	}
	else if (RightCollideCell(board, center) || RightCollideCell(board, corner)
		|| RightCollideCell(board, right) || RightCollideCell(board, down))
	{
		return COLDIR::Right;
	}

	return COLDIR::None;
}

void LRight::Draw()
{
	CUR cursor;

	SetColor(color);

	cursor.gotoxy(ConLoc(center));
	std::cout << "  ";

	cursor.gotoxy(ConLoc(corner));
	std::cout << "  ";

	cursor.gotoxy(ConLoc(right));
	std::cout << "  ";

	cursor.gotoxy(ConLoc(down));
	std::cout << "  ";

	SetColor(defColor);
	cursor.gotoxy(txtPos);
}

void LRight::Place()
{
	current = true;

	center = initPiecePos;
	corner = { center.x - 1, center.y };
	right = { center.x + 1, center.y };
	down = { center.x + 1, center.y + 1 };

	rot = ROT::Up;
	SetRotation();
}

void LRight::QuitFalling(CELL board[maxX][maxY])
{
	board[center.x][center.y].color = color;
	board[center.x][center.y].state = CELLSTATE::Static;

	board[corner.x][corner.y].color = color;
	board[corner.x][corner.y].state = CELLSTATE::Static;

	board[right.x][right.y].color = color;
	board[right.x][right.y].state = CELLSTATE::Static;

	board[down.x][down.y].color = color;
	board[down.x][down.y].state = CELLSTATE::Static;

	current = false;
}

void LRight::FallOne()
{
	center.y++;
	corner.y++;
	right.y++;
	down.y++;
}

void LRight::MoveRight()
{
	center.x++;
	corner.x++;
	right.x++;
	down.x++;
}

void LRight::MoveLeft()
{
	center.x--;
	corner.x--;
	right.x--;
	down.x--;
}

void LRight::RotateRight()
{
	if (rot != ROT::Left)
		rot = (ROT)((int)rot + 1);
	else
		rot = ROT::Up;

	SetRotation();
	Kick();
}

void LRight::RotateLeft()
{
	if (rot != ROT::Up)
		rot = (ROT)((int)rot - 1);
	else
		rot = ROT::Left;

	SetRotation();
	Kick();
}