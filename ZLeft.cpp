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

void ZLeft::UnKick(CELL board[maxX][maxY])
{
	if ((left.x == maxX - 2 || downRight.x == maxX - 2 || down.x == maxX - 2) && !RightColliding(board))
	{
		MoveRight();
	}
	else if ((left.x == 1 || downRight.x == 1 || down.x == 1) && !LeftColliding(board))
	{
		MoveLeft();
	}
}

void ZLeft::Kick()
{
	if (left.x >= maxX || downRight.x >= maxX || down.x >= maxX)
	{
		MoveLeft();
	}
	else if (left.x < 0 || downRight.x < 0 || down.x < 0)
	{
		MoveRight();
	}

	if (left.y >= maxY || downRight.y >= maxY || down.y >= maxY)
	{
		left.y--;
		downRight.y--;
		center.y--;
		down.y--;
	}
}

bool ZLeft::CheckOverlapedCell(CELL board[maxX][maxY])
{
	return (board[left.x][left.y].state == CELLSTATE::Static
		|| board[downRight.x][downRight.y].state == CELLSTATE::Static
		|| board[down.x][down.y].state == CELLSTATE::Static);
}

bool ZLeft::DownColliding(CELL board[maxX][maxY])
{
	if (DownCollideCell(board, center) || DownCollideCell(board, left)
		|| DownCollideCell(board, downRight) || DownCollideCell(board, down))
	{
		QuitFalling(board);
		return true;
	}
	return false;
}

bool ZLeft::LeftColliding(CELL board[maxX][maxY])
{
	if (LeftCollideCell(board, center) || LeftCollideCell(board, left)
		|| LeftCollideCell(board, downRight) || LeftCollideCell(board, down))
	{
		return true;
	}
	return false;
}

bool ZLeft::RightColliding(CELL board[maxX][maxY])
{
	if (RightCollideCell(board, center) || RightCollideCell(board, left)
		|| RightCollideCell(board, downRight) || RightCollideCell(board, down))
	{
		return true;
	}
	return false;
}

void ZLeft::Draw()
{
	CUR cursor;

	SetColor(color);

	cursor.gotoxy(ConLoc(center));
	std::cout << (char)lHalf << (char)rHalf;

	cursor.gotoxy(ConLoc(left));
	std::cout << (char)lHalf << (char)rHalf;

	cursor.gotoxy(ConLoc(downRight));
	std::cout << (char)lHalf << (char)rHalf;

	cursor.gotoxy(ConLoc(down));
	std::cout << (char)lHalf << (char)rHalf;

	SetColor(defColor);
	cursor.gotoxy(txtPos);
}

void ZLeft::DrawAsNext()
{
	COORDS pivotPos = { boardIndent + 16 + maxX, 3 };
	CUR cursor;
	int cont = 2;

	SetColor(color);

	cursor.gotoxy({ pivotPos.x, pivotPos.y });
	std::cout << (char)lHalf << (char)rHalf;

	cursor.gotoxy({ pivotPos.x - cont, pivotPos.y });
	std::cout << (char)lHalf << (char)rHalf;

	cursor.gotoxy({ pivotPos.x + cont, pivotPos.y + 1 });
	std::cout << (char)lHalf << (char)rHalf;

	cursor.gotoxy({ pivotPos.x, pivotPos.y + 1 });
	std::cout << (char)lHalf << (char)rHalf;

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
	board[center.x][center.y].state = CELLSTATE::Static;
	board[center.x][center.y].color = color;
	board[center.x][center.y].skin[0] = lHalf;
	board[center.x][center.y].skin[1] = rHalf;

	board[downRight.x][downRight.y].state = CELLSTATE::Static;
	board[downRight.x][downRight.y].color = color;
	board[downRight.x][downRight.y].skin[0] = lHalf;
	board[downRight.x][downRight.y].skin[1] = rHalf;

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

void ZLeft::FallOne()
{
	center.y++;
	left.y++;
	downRight.y++;
	down.y++;
}

void ZLeft::MoveUp()
{
	center.y--;
	left.y--;
	downRight.y--;
	down.y--;
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

void ZLeft::BurnOnBoard(CELL board[maxX][maxY])
{
	board[center.x][center.y].state = CELLSTATE::Moving;
	board[center.x][center.y].color = color;
	board[center.x][center.y].skin[0] = lHalf;
	board[center.x][center.y].skin[1] = rHalf;

	board[downRight.x][downRight.y].state = CELLSTATE::Moving;
	board[downRight.x][downRight.y].color = color;
	board[downRight.x][downRight.y].skin[0] = lHalf;
	board[downRight.x][downRight.y].skin[1] = rHalf;

	board[left.x][left.y].state = CELLSTATE::Moving;
	board[left.x][left.y].color = color;
	board[left.x][left.y].skin[0] = lHalf;
	board[left.x][left.y].skin[1] = rHalf;

	board[down.x][down.y].state = CELLSTATE::Moving;
	board[down.x][down.y].color = color;
	board[down.x][down.y].skin[0] = lHalf;
	board[down.x][down.y].skin[1] = rHalf;
}

void ZLeft::EraseFromBoard(CELL board[maxX][maxY])
{
	board[center.x][center.y].state = CELLSTATE::Empty;
	board[center.x][center.y].color = defColor;
	board[center.x][center.y].skin[0] = sqr;
	board[center.x][center.y].skin[1] = sqr;

	board[downRight.x][downRight.y].state = CELLSTATE::Empty;
	board[downRight.x][downRight.y].color = defColor;
	board[downRight.x][downRight.y].skin[0] = sqr;
	board[downRight.x][downRight.y].skin[1] = sqr;

	board[left.x][left.y].state = CELLSTATE::Empty;
	board[left.x][left.y].color = defColor;
	board[left.x][left.y].skin[0] = sqr;
	board[left.x][left.y].skin[1] = sqr;

	board[down.x][down.y].state = CELLSTATE::Empty;
	board[down.x][down.y].color = defColor;
	board[down.x][down.y].skin[0] = sqr;
	board[down.x][down.y].skin[1] = sqr;
}