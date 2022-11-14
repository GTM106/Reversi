#pragma once
#include "BoardPoint.h"
#include "Board.h"

class PlayerData
{
	BoardStatus _color;

	void print_board(int h, int v, Board board);
	void input(Board& board);
public:
	PlayerData(BoardStatus color);

	bool turn(Board& board);

	BoardStatus color() { return _color; }
};