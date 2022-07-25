#include "T.h"

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

void T::UnKick(CELL board[maxX][maxY])
{
	if ((left.x == maxX - 2 || right.x == maxX - 2 || down.x == maxX - 2) && !RightColliding(board))
	{
		MoveRight();
	}
	else if ((left.x == 1 || right.x == 1 || down.x == 1) && !LeftColliding(board))
	{
		MoveLeft();
	}
}

void T::Kick()
{
	if (left.x >= maxX || right.x >= maxX || down.x >= maxX)
	{
		MoveLeft();
	}
	else if (left.x < 0 || right.x < 0 || down.x < 0)
	{
		MoveRight();
	}
}

bool T::CheckOverlapedCell(CELL board[maxX][maxY])
{
	return (board[left.x][left.y].state == CELLSTATE::Static
		|| board[right.x][right.y].state == CELLSTATE::Static
		|| board[down.x][down.y].state == CELLSTATE::Static);
}

bool T::DownColliding(CELL board[maxX][maxY])
{
	if (DownCollideCell(board, center) || DownCollideCell(board, left)
		|| DownCollideCell(board, right) || DownCollideCell(board, down))
	{
		QuitFalling(board);
		return true;
	}
	return false;
}

bool T::LeftColliding(CELL board[maxX][maxY])
{
	if (LeftCollideCell(board, center) || LeftCollideCell(board, left)
		|| LeftCollideCell(board, right) || LeftCollideCell(board, down))
	{
		return true;
	}
	return false;
}

bool T::RightColliding(CELL board[maxX][maxY])
{
	if (RightCollideCell(board, center) || RightCollideCell(board, left)
		|| RightCollideCell(board, right) || RightCollideCell(board, down))
	{
		return true;
	}
	return false;
}

void T::Draw()
{
	CUR cursor;

	SetColor(color);

	cursor.gotoxy(ConLoc(center));
	std::cout << sqr << sqr;

	cursor.gotoxy(ConLoc(left));
	std::cout << sqr << sqr;

	cursor.gotoxy(ConLoc(right));
	std::cout << sqr << sqr;

	cursor.gotoxy(ConLoc(down));
	std::cout << sqr << sqr;

	SetColor(defColor);
	cursor.gotoxy(txtPos);
}

void T::DrawAsNext()
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

	cursor.gotoxy({ pivotPos.x, pivotPos.y + 1 });
	std::cout << sqr << sqr;

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

void T::MoveUp()
{
	center.y--;
	left.y--;
	right.y--;
	down.y--;
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

void T::BurnOnBoard(CELL board[maxX][maxY])
{
	board[center.x][center.y].state = CELLSTATE::Moving;
	board[center.x][center.y].color = color;

	board[left.x][left.y].state = CELLSTATE::Moving;
	board[left.x][left.y].color = color;

	board[right.x][right.y].state = CELLSTATE::Moving;
	board[right.x][right.y].color = color;

	board[down.x][down.y].state = CELLSTATE::Moving;
	board[down.x][down.y].color = color;
}

void T::EraseFromBoard(CELL board[maxX][maxY])
{
	board[center.x][center.y].state = CELLSTATE::Empty;
	board[center.x][center.y].color = defColor;

	board[left.x][left.y].state = CELLSTATE::Empty;
	board[left.x][left.y].color = defColor;

	board[right.x][right.y].state = CELLSTATE::Empty;
	board[right.x][right.y].color = defColor;

	board[down.x][down.y].state = CELLSTATE::Empty;
	board[down.x][down.y].color = defColor;
}