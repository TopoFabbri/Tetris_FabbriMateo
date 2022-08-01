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

void Stick::UnKick(CELL board[maxX][maxY])
{
	if ((left.x == maxX - 2 || right.x == maxX - 2 || centerRight.x == maxX - 2) && !RightColliding(board))
	{
		MoveRight();
	}
	else if ((left.x == 1 || right.x == 1 || centerRight.x == 1) && !LeftColliding(board))
	{
		MoveLeft();
	}

	if ((left.x == maxX - 2 || right.x == maxX - 2 || centerRight.x == maxX - 2) && !RightColliding(board))
	{
		MoveRight();
	}
	else if ((left.x == 1 || right.x == 1 || centerRight.x == 1) && !LeftColliding(board))
	{
		MoveLeft();
	}
}

void Stick::Kick()
{
	if (left.x >= maxX || right.x >= maxX || centerRight.x >= maxX)
	{
		MoveLeft();
	}
	else if (left.x < 0 || right.x < 0 || centerRight.x < 0)
	{
		MoveRight();
	}

	if (left.y >= maxY || right.y >= maxY || centerRight.y >= maxY)
	{
		left.y--;
		right.y--;
		centerLeft.y--;
		centerRight.y--;
	}

	if (left.x >= maxX || right.x >= maxX || centerRight.x >= maxX)
	{
		MoveLeft();
	}
	else if (left.x < 0 || right.x < 0 || centerRight.x < 0)
	{
		MoveRight();
	}

	if (left.y >= maxY || right.y >= maxY || centerRight.y >= maxY)
	{
		left.y--;
		right.y--;
		centerLeft.y--;
		centerRight.y--;
	}
}

bool Stick::CheckOverlapedCell(CELL board[maxX][maxY])
{
	return (board[left.x][left.y].state == CELLSTATE::Static
		|| board[right.x][right.y].state == CELLSTATE::Static
		|| board[centerRight.x][centerRight.y].state == CELLSTATE::Static);
}

bool Stick::DownColliding(CELL board[maxX][maxY])
{
	if (DownCollideCell(board, centerLeft) || DownCollideCell(board, left)
		|| DownCollideCell(board, right) || DownCollideCell(board, centerRight))
	{
		QuitFalling(board);
		return true;
	}
	return false;
}

bool Stick::LeftColliding(CELL board[maxX][maxY])
{
	if (LeftCollideCell(board, centerLeft) || LeftCollideCell(board, left)
		|| LeftCollideCell(board, right) || LeftCollideCell(board, centerRight))
	{
		return true;
	}
	return false;
}

bool Stick::RightColliding(CELL board[maxX][maxY])
{
	if (RightCollideCell(board, centerLeft) || RightCollideCell(board, left)
		|| RightCollideCell(board, right) || RightCollideCell(board, centerRight))
	{
		return true;
	}
	return false;
}

void Stick::Draw()
{
	CUR cursor;

	SetColor(color);

	cursor.gotoxy(ConLoc(centerLeft));
	std::cout << (char)lHalf << (char)rHalf;

	cursor.gotoxy(ConLoc(left));
	std::cout << (char)lHalf << (char)rHalf;

	cursor.gotoxy(ConLoc(right));
	std::cout << (char)lHalf << (char)rHalf;

	cursor.gotoxy(ConLoc(centerRight));
	std::cout << (char)lHalf << (char)rHalf;

	SetColor(defColor);
	cursor.gotoxy(txtPos);
}

void Stick::DrawAsNext()
{
	COORDS pivotPos = { boardIndent + 15 + maxX, 3 };
	CUR cursor;
	int cont = 2;

	SetColor(color);

	cursor.gotoxy(pivotPos);
	std::cout << (char)lHalf << (char)rHalf;

	cursor.gotoxy({ pivotPos.x - cont, pivotPos.y });
	std::cout << (char)lHalf << (char)rHalf;

	cursor.gotoxy({ pivotPos.x + cont * 2, pivotPos.y });
	std::cout << (char)lHalf << (char)rHalf;

	cursor.gotoxy({ pivotPos.x + cont, pivotPos.y });
	std::cout << (char)lHalf << (char)rHalf;

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
	board[centerLeft.x][centerLeft.y].state = CELLSTATE::Static;
	board[centerLeft.x][centerLeft.y].color = color;
	board[centerLeft.x][centerLeft.y].skin[0] = lHalf;
	board[centerLeft.x][centerLeft.y].skin[1] = rHalf;

	board[left.x][left.y].state = CELLSTATE::Static;
	board[left.x][left.y].color = color;
	board[left.x][left.y].skin[0] = lHalf;
	board[left.x][left.y].skin[1] = rHalf;

	board[centerRight.x][centerRight.y].state = CELLSTATE::Static;
	board[centerRight.x][centerRight.y].color = color;
	board[centerRight.x][centerRight.y].skin[0] = lHalf;
	board[centerRight.x][centerRight.y].skin[1] = rHalf;

	board[right.x][right.y].state = CELLSTATE::Static;
	board[right.x][right.y].color = color;
	board[right.x][right.y].skin[0] = lHalf;
	board[right.x][right.y].skin[1] = rHalf;

	current = false;
}

void Stick::FallOne()
{
	centerLeft.y++;
	left.y++;
	right.y++;
	centerRight.y++;
}

void Stick::MoveUp()
{
	centerLeft.y--;
	left.y--;
	right.y--;
	centerRight.y--;
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

void Stick::BurnOnBoard(CELL board[maxX][maxY])
{
	board[centerLeft.x][centerLeft.y].state = CELLSTATE::Moving;
	board[centerLeft.x][centerLeft.y].color = color;
	board[centerLeft.x][centerLeft.y].skin[0] = lHalf;
	board[centerLeft.x][centerLeft.y].skin[1] = rHalf;

	board[left.x][left.y].state = CELLSTATE::Moving;
	board[left.x][left.y].color = color;
	board[left.x][left.y].skin[0] = lHalf;
	board[left.x][left.y].skin[1] = rHalf;

	board[centerRight.x][centerRight.y].state = CELLSTATE::Moving;
	board[centerRight.x][centerRight.y].color = color;
	board[centerRight.x][centerRight.y].skin[0] = lHalf;
	board[centerRight.x][centerRight.y].skin[1] = rHalf;

	board[right.x][right.y].state = CELLSTATE::Moving;
	board[right.x][right.y].color = color;
	board[right.x][right.y].skin[0] = lHalf;
	board[right.x][right.y].skin[1] = rHalf;
}

void Stick::EraseFromBoard(CELL board[maxX][maxY])
{
	board[centerLeft.x][centerLeft.y].state = CELLSTATE::Empty;
	board[centerLeft.x][centerLeft.y].color = defColor;
	board[right.x][right.y].skin[0] = sqr;
	board[right.x][right.y].skin[1] = sqr;

	board[left.x][left.y].state = CELLSTATE::Empty;
	board[left.x][left.y].color = defColor;
	board[right.x][right.y].skin[0] = sqr;
	board[right.x][right.y].skin[1] = sqr;

	board[centerRight.x][centerRight.y].state = CELLSTATE::Empty;
	board[centerRight.x][centerRight.y].color = defColor;
	board[right.x][right.y].skin[0] = sqr;
	board[right.x][right.y].skin[1] = sqr;

	board[right.x][right.y].state = CELLSTATE::Empty;
	board[right.x][right.y].color = defColor;
	board[right.x][right.y].skin[0] = sqr;
	board[right.x][right.y].skin[1] = sqr;
}