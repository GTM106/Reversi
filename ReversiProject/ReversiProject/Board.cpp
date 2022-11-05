#include "Board.h"

Board::Board(BoardStatus status)
{
	_status = status;
	_can_placed = false;
}

void Board::set_can_placed(bool enable)
{
	_can_placed = enable;
}

void Board::set_status(BoardStatus status)
{
	_status = status;
}