#pragma once
#include "BoardPoint.h"
#include "Vector2Int.h"
#include "Board.h"

class PlayerData
{
	BoardStatus _color;

	Vector2Int _selectPos;

	void print_board(int h, int v, Board board);
	void input(Board& board);
public:
	PlayerData(BoardStatus color);

	void turn(Board& board);

	BoardStatus color() { return _color; }
	Vector2Int selectPos() { return _selectPos; }

	void set_selectPos(Vector2Int vec);
};