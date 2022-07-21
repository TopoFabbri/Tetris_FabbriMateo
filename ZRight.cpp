#include "ZRight.h"

bool ZRight::DownCollideCell(CELL board[maxX][maxY], COORDS cell)
{
	return (board[cell.x][cell.y + 1].state == CELLSTATE::Static || cell.y >= maxY - 1);
}

bool ZRight::LeftCollideCell(CELL board[maxX][maxY], COORDS cell)
{
	return (board[cell.x - 1][cell.y].state == CELLSTATE::Static || cell.x <= 0);
}

bool ZRight::RightCollideCell(CELL board[maxX][maxY], COORDS cell)
{
	return (board[cell.x + 1][cell.y].state == CELLSTATE::Static || cell.x >= maxX - 1);
}

void ZRight::SetRotation()
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

void ZRight::RotationUp()
{
	downLeft = { center.x - 1, center.y + 1 };
	right = { center.x + 1, center.y };
	down = { center.x, center.y + 1 };
}

void ZRight::RotationRight()
{
	downLeft = { center.x - 1, center.y - 1 };
	right = { center.x, center.y + 1 };
	down = { center.x - 1, center.y };
}

void ZRight::RotationLeft()
{
	downLeft = { center.x + 1, center.y + 1 };
	right = { center.x, center.y - 1 };
	down = { center.x + 1, center.y };
}

void ZRight::RotationDown()
{
	downLeft = { center.x + 1, center.y - 1 };
	right = { center.x - 1, center.y };
	down = { center.x, center.y - 1 };
}

void ZRight::Kick()
{
	if (downLeft.x >= maxX - 1 || right.x >= maxX - 1 || down.x >= maxX - 1)
	{
		MoveLeft();
	}
	else if (downLeft.x <= 0 || right.x <= 0 || down.x <= 0)
	{
		MoveRight();
	}
}

bool ZRight::CheckOverlapedCell(CELL board[maxX][maxY])
{
	return (board[downLeft.x][downLeft.y].state == CELLSTATE::Static
		|| board[right.x][right.y].state == CELLSTATE::Static
		|| board[down.x][down.y].state == CELLSTATE::Static);
}

bool ZRight::DownColliding(CELL board[maxX][maxY])
{
	if (DownCollideCell(board, center) || DownCollideCell(board, downLeft)
		|| DownCollideCell(board, right) || DownCollideCell(board, down))
	{
		QuitFalling(board);
		return true;
	}

	return false;
}

bool ZRight::LeftColliding(CELL board[maxX][maxY])
{
	if (LeftCollideCell(board, center) || LeftCollideCell(board, downLeft)
		|| LeftCollideCell(board, right) || LeftCollideCell(board, down))
	{
		return true;
	}

	return false;
}

bool ZRight::RightColliding(CELL board[maxX][maxY])
{
	if (RightCollideCell(board, center) || RightCollideCell(board, downLeft)
		|| RightCollideCell(board, right) || RightCollideCell(board, down))
	{
		return true;
	}

	return false;
}

void ZRight::Draw()
{
	CUR cursor;

	SetColor(color);

	cursor.gotoxy(ConLoc(center));
	std::cout << sqr << sqr;

	cursor.gotoxy(ConLoc(downLeft));
	std::cout << sqr << sqr;

	cursor.gotoxy(ConLoc(right));
	std::cout << sqr << sqr;

	cursor.gotoxy(ConLoc(down));
	std::cout << sqr << sqr;

	SetColor(defColor);
	cursor.gotoxy(txtPos);
}

void ZRight::DrawAsNext()
{
	COORDS pivotPos = { boardIndent + 20 + maxX, 1 };
	CUR cursor;
	int cont = 2;

	SetColor(color);

	cursor.gotoxy({ pivotPos.x, pivotPos.y });
	std::cout << sqr << sqr;

	cursor.gotoxy({ pivotPos.x - cont, pivotPos.y + 1 });
	std::cout << sqr << sqr;

	cursor.gotoxy({ pivotPos.x + cont, pivotPos.y });
	std::cout << sqr << sqr;

	cursor.gotoxy({ pivotPos.x, pivotPos.y + 1 });
	std::cout << sqr << sqr;

	SetColor(defColor);
	cursor.gotoxy(txtPos);
}

void ZRight::Place()
{
	current = true;

	center = initPiecePos;
	downLeft = { center.x - 1, center.y + 1 };
	right = { center.x + 1, center.y };
	down = { center.x, center.y + 1 };

	rot = ROT::Up;
	SetRotation();
}

void ZRight::QuitFalling(CELL board[maxX][maxY])
{
	board[center.x][center.y].color = color;
	board[center.x][center.y].state = CELLSTATE::Static;

	board[downLeft.x][downLeft.y].color = color;
	board[downLeft.x][downLeft.y].state = CELLSTATE::Static;

	board[right.x][right.y].color = color;
	board[right.x][right.y].state = CELLSTATE::Static;

	board[down.x][down.y].color = color;
	board[down.x][down.y].state = CELLSTATE::Static;

	current = false;
}

void ZRight::FallOne()
{
	center.y++;
	downLeft.y++;
	right.y++;
	down.y++;
}

void ZRight::MoveUp()
{
	center.y--;
	downLeft.y--;
	right.y--;
	down.y--;
}

void ZRight::MoveRight()
{
	center.x++;
	downLeft.x++;
	right.x++;
	down.x++;
}

void ZRight::MoveLeft()
{
	center.x--;
	downLeft.x--;
	right.x--;
	down.x--;
}

void ZRight::RotateRight()
{
	if (rot != ROT::Left)
		rot = (ROT)((int)rot + 1);
	else
		rot = ROT::Up;

	SetRotation();
	Kick();
}

void ZRight::RotateLeft()
{
	if (rot != ROT::Up)
		rot = (ROT)((int)rot - 1);
	else
		rot = ROT::Left;

	SetRotation();
	Kick();
}

void ZRight::BurnOnBoard(CELL board[maxX][maxY])
{
	board[center.x][center.y].state = CELLSTATE::Moving;
	board[center.x][center.y].color = color;

	board[downLeft.x][downLeft.y].state = CELLSTATE::Moving;
	board[downLeft.x][downLeft.y].color = color;

	board[right.x][right.y].state = CELLSTATE::Moving;
	board[right.x][right.y].color = color;

	board[down.x][down.y].state = CELLSTATE::Moving;
	board[down.x][down.y].color = color;
}

void ZRight::EraseFromBoard(CELL board[maxX][maxY])
{
	board[center.x][center.y].state = CELLSTATE::Empty;
	board[center.x][center.y].color = defColor;

	board[downLeft.x][downLeft.y].state = CELLSTATE::Empty;
	board[downLeft.x][downLeft.y].color = defColor;

	board[right.x][right.y].state = CELLSTATE::Empty;
	board[right.x][right.y].color = defColor;

	board[down.x][down.y].state = CELLSTATE::Empty;
	board[down.x][down.y].color = defColor;
}