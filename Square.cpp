#include "Square.h"

bool Square::DownCollideCell(CELL board[maxX][maxY], COORDS cell)
{
	return (board[cell.x][cell.y + 1].state == CELLSTATE::Static || cell.y >= maxY - 1);
}

bool Square::LeftCollideCell(CELL board[maxX][maxY], COORDS cell)
{
	return (board[cell.x - 1][cell.y].state == CELLSTATE::Static || cell.x <= 0);
}

bool Square::RightCollideCell(CELL board[maxX][maxY], COORDS cell)
{
	return (board[cell.x + 1][cell.y].state == CELLSTATE::Static || cell.x >= maxX - 1);
}

COLDIR Square::GetCollisions(CELL board[maxX][maxY])
{
	if (DownCollideCell(board, upLeft) || DownCollideCell(board, upRight)
		|| DownCollideCell(board, lowLeft) || DownCollideCell(board, lowRight))
	{
		QuitFalling(board);
		return COLDIR::Down;
	}
	else if (LeftCollideCell(board, upLeft) || LeftCollideCell(board, upRight)
		|| LeftCollideCell(board, lowLeft) || LeftCollideCell(board, lowRight))
	{
		return COLDIR::Left;
	}
	else if (RightCollideCell(board, upLeft) || RightCollideCell(board, upRight)
		|| RightCollideCell(board, lowLeft) || RightCollideCell(board, lowRight))
	{
		return COLDIR::Right;
	}

	return COLDIR::None;
}

void Square::Place()
{
	current = true;

	upLeft = initPiecePos;
	upRight = { upLeft.x + 1, upLeft.y };
	lowLeft = { upLeft.x, upLeft.y + 1 };
	lowRight = { upLeft.x + 1, upLeft.y + 1 };
}

void Square::QuitFalling(CELL board[maxX][maxY])
{
	board[upLeft.x][upLeft.y].color = color;
	board[upLeft.x][upLeft.y].state = CELLSTATE::Static;

	board[upRight.x][upRight.y].color = color;
	board[upRight.x][upRight.y].state = CELLSTATE::Static;

	board[lowLeft.x][lowLeft.y].color = color;
	board[lowLeft.x][lowLeft.y].state = CELLSTATE::Static;

	board[lowRight.x][lowRight.y].color = color;
	board[lowRight.x][lowRight.y].state = CELLSTATE::Static;

	current = false;
}

void Square::Draw()
{
	CUR cursor;

	SetColor(color);

	cursor.gotoxy(ConLoc(upLeft));
	std::cout << sqr << sqr;

	cursor.gotoxy(ConLoc(upRight));
	std::cout << sqr << sqr;

	cursor.gotoxy(ConLoc(lowLeft));
	std::cout << sqr << sqr;

	cursor.gotoxy(ConLoc(lowRight));
	std::cout << sqr << sqr;

	SetColor(defColor);
	cursor.gotoxy(txtPos);
}

void Square::FallOne()
{
	upLeft.y++;
	upRight.y++;
	lowLeft.y++;
	lowRight.y++;
}

void Square::MoveRight()
{
	upLeft.x++;
	upRight.x++;
	lowLeft.x++;
	lowRight.x++;
}

void Square::MoveLeft()
{
	upLeft.x--;
	upRight.x--;
	lowLeft.x--;
	lowRight.x--;
}