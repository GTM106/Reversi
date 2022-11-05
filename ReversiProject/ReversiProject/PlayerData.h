#pragma once
#include <vector>
#include "Board.h"

class PlayerData
{
	BoardStatus _color;

	void print_board(int h, int v, std::vector<std::vector<Board>> board);
	void input(std::vector<std::vector<Board>>& board);
public:
	PlayerData(BoardStatus color);

	void turn(std::vector<std::vector<Board>>& board);

	BoardStatus color() { return _color; }
};