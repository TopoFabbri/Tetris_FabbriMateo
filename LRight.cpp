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

void LRight::UnKick(CELL board[maxX][maxY])
{
	if ((corner.x == maxX - 2 || right.x == maxX - 2 || down.x == maxX - 2) && !RightColliding(board))
	{
		MoveRight();
	}
	else if ((corner.x == 1 || right.x == 1 || down.x == 1) && !LeftColliding(board))
	{
		MoveLeft();
	}
}

void LRight::Kick()
{
	if (corner.x >= maxX || right.x >= maxX || down.x >= maxX)
	{
		MoveLeft();
	}
	else if (corner.x < 0 || right.x < 0 || down.x < 0)
	{
		MoveRight();
	}

	if (corner.y >= maxY || right.y >= maxY || down.y >= maxY)
	{
		corner.y--;
		right.y--;
		center.y--;
		down.y--;
	}
}

bool LRight::CheckOverlapedCell(CELL board[maxX][maxY])
{
	return (board[corner.x][corner.y].state == CELLSTATE::Static
		|| board[right.x][right.y].state == CELLSTATE::Static
		|| board[down.x][down.y].state == CELLSTATE::Static);
}

bool LRight::DownColliding(CELL board[maxX][maxY])
{
	if (DownCollideCell(board, center) || DownCollideCell(board, corner)
		|| DownCollideCell(board, right) || DownCollideCell(board, down))
	{
		QuitFalling(board);
		return true;
	}
	return false;
}

bool LRight::LeftColliding(CELL board[maxX][maxY])
{
	if (LeftCollideCell(board, center) || LeftCollideCell(board, corner)
		|| LeftCollideCell(board, right) || LeftCollideCell(board, down))
	{
		return true;
	}
	return false;
}

bool LRight::RightColliding(CELL board[maxX][maxY])
{
	if (RightCollideCell(board, center) || RightCollideCell(board, corner)
		|| RightCollideCell(board, right) || RightCollideCell(board, down))
	{
		return true;
	}
	return false;
}

void LRight::Draw()
{
	CUR cursor;

	SetColor(color);

	cursor.gotoxy(ConLoc(center));
	std::cout << (char)lHalf << (char)rHalf;

	cursor.gotoxy(ConLoc(corner));
	std::cout << (char)lHalf << (char)rHalf;

	cursor.gotoxy(ConLoc(right));
	std::cout << (char)lHalf << (char)rHalf;

	cursor.gotoxy(ConLoc(down));
	std::cout << (char)lHalf << (char)rHalf;

	SetColor(defColor);
	cursor.gotoxy(txtPos);
}

void LRight::DrawAsNext()
{
	COORDS pivotPos = { boardIndent + 16 + maxX, 3 };
	CUR cursor;
	int cont = 2;

	SetColor(color);

	cursor.gotoxy({ pivotPos.x, pivotPos.y });
	std::cout << (char)lHalf << (char)rHalf;

	cursor.gotoxy({ pivotPos.x - cont, pivotPos.y });
	std::cout << (char)lHalf << (char)rHalf;

	cursor.gotoxy({ pivotPos.x + cont, pivotPos.y });
	std::cout << (char)lHalf << (char)rHalf;

	cursor.gotoxy({ pivotPos.x - cont, pivotPos.y + 1 });
	std::cout << (char)lHalf << (char)rHalf;

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
	board[center.x][center.y].state = CELLSTATE::Static;
	board[center.x][center.y].color = color;
	board[center.x][center.y].skin[0] = lHalf;
	board[center.x][center.y].skin[1] = rHalf;

	board[corner.x][corner.y].state = CELLSTATE::Static;
	board[corner.x][corner.y].color = color;
	board[corner.x][corner.y].skin[0] = lHalf;
	board[corner.x][corner.y].skin[1] = rHalf;

	board[right.x][right.y].state = CELLSTATE::Static;
	board[right.x][right.y].color = color;
	board[right.x][right.y].skin[0] = lHalf;
	board[right.x][right.y].skin[1] = rHalf;

	board[down.x][down.y].state = CELLSTATE::Static;
	board[down.x][down.y].color = color;
	board[down.x][down.y].skin[0] = lHalf;
	board[down.x][down.y].skin[1] = rHalf;

	current = false;
}

void LRight::FallOne()
{
	center.y++;
	corner.y++;
	right.y++;
	down.y++;
}

void LRight::MoveUp()
{
	center.y--;
	corner.y--;
	right.y--;
	down.y--;
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

void LRight::BurnOnBoard(CELL board[maxX][maxY])
{
	board[center.x][center.y].state = CELLSTATE::Moving;
	board[center.x][center.y].color = color;
	board[center.x][center.y].skin[0] = lHalf;
	board[center.x][center.y].skin[1] = rHalf;

	board[corner.x][corner.y].state = CELLSTATE::Moving;
	board[corner.x][corner.y].color = color;
	board[corner.x][corner.y].skin[0] = lHalf;
	board[corner.x][corner.y].skin[1] = rHalf;

	board[right.x][right.y].state = CELLSTATE::Moving;
	board[right.x][right.y].color = color;
	board[right.x][right.y].skin[0] = lHalf;
	board[right.x][right.y].skin[1] = rHalf;

	board[down.x][down.y].state = CELLSTATE::Moving;
	board[down.x][down.y].color = color;
	board[down.x][down.y].skin[0] = lHalf;
	board[down.x][down.y].skin[1] = rHalf;
}

void LRight::EraseFromBoard(CELL board[maxX][maxY])
{
	board[center.x][center.y].state = CELLSTATE::Empty;
	board[center.x][center.y].color = defColor;
	board[center.x][center.y].skin[0] = sqr;
	board[center.x][center.y].skin[1] = sqr;

	board[corner.x][corner.y].state = CELLSTATE::Empty;
	board[corner.x][corner.y].color = defColor;
	board[corner.x][corner.y].skin[0] = sqr;
	board[corner.x][corner.y].skin[1] = sqr;

	board[right.x][right.y].state = CELLSTATE::Empty;
	board[right.x][right.y].color = defColor;
	board[right.x][right.y].skin[0] = sqr;
	board[right.x][right.y].skin[1] = sqr;

	board[down.x][down.y].state = CELLSTATE::Empty;
	board[down.x][down.y].color = defColor;
	board[down.x][down.y].skin[0] = sqr;
	board[down.x][down.y].skin[1] = sqr;
}