#include "LLeft.h"

bool LLeft::DownCollideCell(CELL board[maxX][maxY], COORDS cell)
{
	return (board[cell.x][cell.y + 1].state == CELLSTATE::Static || cell.y >= maxY - 1);
}

bool LLeft::LeftCollideCell(CELL board[maxX][maxY], COORDS cell)
{
	return (board[cell.x - 1][cell.y].state == CELLSTATE::Static || cell.x <= 0);
}

bool LLeft::RightCollideCell(CELL board[maxX][maxY], COORDS cell)
{
	return (board[cell.x + 1][cell.y].state == CELLSTATE::Static || cell.x >= maxX - 1);
}

void LLeft::SetRotation()
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

void LLeft::RotationUp()
{
	left = { center.x - 1, center.y };
	corner = { center.x + 1, center.y };
	down = { center.x + 1, center.y + 1 };
}

void LLeft::RotationRight()
{
	left = { center.x, center.y - 1 };
	corner = { center.x, center.y + 1 };
	down = { center.x - 1, center.y + 1 };
}

void LLeft::RotationLeft()
{
	left = { center.x, center.y + 1 };
	corner = { center.x, center.y - 1 };
	down = { center.x + 1, center.y - 1 };
}

void LLeft::RotationDown()
{
	left = { center.x + 1, center.y };
	corner = { center.x - 1, center.y };
	down = { center.x - 1, center.y - 1 };
}

void LLeft::Kick()
{
	if (left.x >= maxX - 1 || corner.x >= maxX - 1 || down.x >= maxX - 1)
	{
		MoveLeft();
	}
	else if (left.x <= 0 || corner.x <= 0 || down.x <= 0)
	{
		MoveRight();
	}
}

bool LLeft::CheckOverlapedCell(CELL board[maxX][maxY])
{
	return (board[left.x][left.y].state == CELLSTATE::Static
		|| board[corner.x][corner.y].state == CELLSTATE::Static
		|| board[down.x][down.y].state == CELLSTATE::Static);
}

bool LLeft::DownColliding(CELL board[maxX][maxY])
{
	if (DownCollideCell(board, center) || DownCollideCell(board, left)
		|| DownCollideCell(board, corner) || DownCollideCell(board, down))
	{
		QuitFalling(board);
		return true;
	}
	return false;
}

bool LLeft::LeftColliding(CELL board[maxX][maxY])
{
	if (LeftCollideCell(board, center) || LeftCollideCell(board, left)
		|| LeftCollideCell(board, corner) || LeftCollideCell(board, down))
	{
		return true;
	}
	return false;
}

bool LLeft::RightColliding(CELL board[maxX][maxY])
{
	if (RightCollideCell(board, center) || RightCollideCell(board, left)
		|| RightCollideCell(board, corner) || RightCollideCell(board, down))
	{
		return true;
	}
	return false;
}

void LLeft::Draw()
{
	CUR cursor;

	SetColor(color);

	cursor.gotoxy(ConLoc(center));
	std::cout << sqr << sqr;

	cursor.gotoxy(ConLoc(left));
	std::cout << sqr << sqr;

	cursor.gotoxy(ConLoc(corner));
	std::cout << sqr << sqr;

	cursor.gotoxy(ConLoc(down));
	std::cout << sqr << sqr;

	SetColor(defColor);
	cursor.gotoxy(txtPos);
}

void LLeft::DrawAsNext()
{
	COORDS pivotPos = { boardIndent + 16 + maxX, 3 };
	CUR cursor;
	int cont = 2;

	SetColor(color);

	cursor.gotoxy(pivotPos);
	std::cout << sqr << sqr;

	cursor.gotoxy({ pivotPos.x - cont, pivotPos.y });
	std::cout << sqr << sqr;

	cursor.gotoxy({ pivotPos.x + cont, pivotPos.y });
	std::cout << sqr << sqr;

	cursor.gotoxy({ pivotPos.x + cont, pivotPos.y + 1 });
	std::cout << sqr << sqr;

	SetColor(defColor);
	cursor.gotoxy(txtPos);
}

void LLeft::Place()
{
	current = true;

	center = initPiecePos;
	left = { center.x - 1, center.y };
	corner = { center.x + 1, center.y };
	down = { center.x + 1, center.y + 1 };

	rot = ROT::Up;
	SetRotation();
}

void LLeft::QuitFalling(CELL board[maxX][maxY])
{
	board[center.x][center.y].color = color;
	board[center.x][center.y].state = CELLSTATE::Static;

	board[left.x][left.y].color = color;
	board[left.x][left.y].state = CELLSTATE::Static;

	board[corner.x][corner.y].color = color;
	board[corner.x][corner.y].state = CELLSTATE::Static;

	board[down.x][down.y].color = color;
	board[down.x][down.y].state = CELLSTATE::Static;

	current = false;
}

void LLeft::FallOne()
{
	center.y++;
	left.y++;
	corner.y++;
	down.y++;
}

void LLeft::MoveUp()
{
	center.y--;
	left.y--;
	corner.y--;
	down.y--;
}

void LLeft::MoveRight()
{
	center.x++;
	left.x++;
	corner.x++;
	down.x++;
}

void LLeft::MoveLeft()
{
	center.x--;
	left.x--;
	corner.x--;
	down.x--;
}

void LLeft::RotateRight()
{
	if (rot != ROT::Left)
		rot = (ROT)((int)rot + 1);
	else
		rot = ROT::Up;

	SetRotation();
	Kick();
}

void LLeft::RotateLeft()
{
	if (rot != ROT::Up)
		rot = (ROT)((int)rot - 1);
	else
		rot = ROT::Left;

	SetRotation();
	Kick();
}

void LLeft::BurnOnBoard(CELL board[maxX][maxY])
{
	board[center.x][center.y].state = CELLSTATE::Moving;
	board[center.x][center.y].color = color;

	board[corner.x][corner.y].state = CELLSTATE::Moving;
	board[corner.x][corner.y].color = color;

	board[left.x][left.y].state = CELLSTATE::Moving;
	board[left.x][left.y].color = color;

	board[down.x][down.y].state = CELLSTATE::Moving;
	board[down.x][down.y].color = color;
}

void LLeft::EraseFromBoard(CELL board[maxX][maxY])
{
	board[center.x][center.y].state = CELLSTATE::Empty;
	board[center.x][center.y].color = defColor;

	board[corner.x][corner.y].state = CELLSTATE::Empty;
	board[corner.x][corner.y].color = defColor;

	board[left.x][left.y].state = CELLSTATE::Empty;
	board[left.x][left.y].color = defColor;

	board[down.x][down.y].state = CELLSTATE::Empty;
	board[down.x][down.y].color = defColor;
}