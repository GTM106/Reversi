#pragma once
#include "BoardPoint.h"
#include "Board.h"
#include "ITurn.h"

class AIData : public ITurn
{
	BoardStatus _color;

	int depth;

public:
	AIData(BoardStatus color);

	bool turn(Board& board);

	BoardStatus color() { return _color; }
};