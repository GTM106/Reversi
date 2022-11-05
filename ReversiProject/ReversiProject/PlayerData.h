#pragma once
#include <vector>
#include "Board.h"

class PlayerData
{
	BoardStatus _color;

public:
	PlayerData(BoardStatus color);

	void turn(std::vector<std::vector<Board>> board);

	BoardStatus color() { return _color; }
};