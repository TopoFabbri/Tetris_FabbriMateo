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

void LLeft::UnKick(CELL board[maxX][maxY])
{
	if ((left.x == maxX - 2 || corner.x == maxX - 2 || down.x == maxX - 2) && !RightColliding(board))
	{
		MoveRight();
	}
	else if ((left.x == 1 || corner.x == 1 || down.x == 1) && !LeftColliding(board))
	{
		MoveLeft();
	}
}

void LLeft::Kick()
{
	if (left.x >= maxX || corner.x >= maxX || down.x >= maxX)
	{
		MoveLeft();
	}
	else if (left.x < 0 || corner.x < 0 || down.x < 0)
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
	CUR cursor{};

	SetColor(color);

	cursor.gotoxy(ConLoc(center));
	std::cout << (char)lHalf << (char)rHalf;

	cursor.gotoxy(ConLoc(left));
	std::cout << (char)lHalf << (char)rHalf;

	cursor.gotoxy(ConLoc(corner));
	std::cout << (char)lHalf << (char)rHalf;

	cursor.gotoxy(ConLoc(down));
	std::cout << (char)lHalf << (char)rHalf;

	SetColor(defColor);
	cursor.gotoxy(txtPos);
}

void LLeft::DrawAsNext()
{
	const COORDS pivotPos = { boardIndent + 16 + maxX, 3 };
	CUR cursor;
	const int cont = 2;

	SetColor(color);

	cursor.gotoxy(pivotPos);
	std::cout << (char)lHalf << (char)rHalf;

	cursor.gotoxy({ pivotPos.x - cont, pivotPos.y });
	std::cout << (char)lHalf << (char)rHalf;

	cursor.gotoxy({ pivotPos.x + cont, pivotPos.y });
	std::cout << (char)lHalf << (char)rHalf;

	cursor.gotoxy({ pivotPos.x + cont, pivotPos.y + 1 });
	std::cout << (char)lHalf << (char)rHalf;

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
	board[center.x][center.y].state = CELLSTATE::Static;
	board[center.x][center.y].color = color;
	board[center.x][center.y].skin[0] = lHalf;
	board[center.x][center.y].skin[1] = rHalf;

	board[corner.x][corner.y].state = CELLSTATE::Static;
	board[corner.x][corner.y].color = color;
	board[corner.x][corner.y].skin[0] = lHalf;
	board[corner.x][corner.y].skin[1] = rHalf;

	board[left.x][left.y].state = CELLSTATE::Static;
	board[left.x][left.y].color = color;
	board[left.x][left.y].skin[0] = lHalf;
	board[left.x][left.y].skin[1] = rHalf;

	board[down.x][down.y].state = CELLSTATE::Static;
	board[down.x][down.y].color = color;
	board[down.x][down.y].skin[0] = lHalf;
	board[down.x][down.y].skin[1] = rHalf;

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
	board[center.x][center.y].skin[0] = lHalf;
	board[center.x][center.y].skin[1] = rHalf;

	board[corner.x][corner.y].state = CELLSTATE::Moving;
	board[corner.x][corner.y].color = color;
	board[corner.x][corner.y].skin[0] = lHalf;
	board[corner.x][corner.y].skin[1] = rHalf;

	board[left.x][left.y].state = CELLSTATE::Moving;
	board[left.x][left.y].color = color;
	board[left.x][left.y].skin[0] = lHalf;
	board[left.x][left.y].skin[1] = rHalf;

	board[down.x][down.y].state = CELLSTATE::Moving;
	board[down.x][down.y].color = color;
	board[down.x][down.y].skin[0] = lHalf;
	board[down.x][down.y].skin[1] = rHalf;
}

void LLeft::EraseFromBoard(CELL board[maxX][maxY])
{
	board[center.x][center.y].state = CELLSTATE::Empty;
	board[center.x][center.y].color = defColor;
	board[down.x][down.y].skin[0] = sqr;
	board[down.x][down.y].skin[1] = sqr;

	board[corner.x][corner.y].state = CELLSTATE::Empty;
	board[corner.x][corner.y].color = defColor;
	board[down.x][down.y].skin[0] = sqr;
	board[down.x][down.y].skin[1] = sqr;

	board[left.x][left.y].state = CELLSTATE::Empty;
	board[left.x][left.y].color = defColor;
	board[down.x][down.y].skin[0] = sqr;
	board[down.x][down.y].skin[1] = sqr;

	board[down.x][down.y].state = CELLSTATE::Empty;
	board[down.x][down.y].color = defColor;
	board[down.x][down.y].skin[0] = sqr;
	board[down.x][down.y].skin[1] = sqr;
}