#pragma once
#include "BoardPoint.h"
#include "Board.h"
#include "ITurn.h"
#include "Vector2Int.h"
#include "Evaluator.h"

class AIData : public ITurn
{
	BoardStatus _color;
	std::unique_ptr<Evaluator> evaluator;

	int eval;

	void put(Board& board);
	void random(Board& board);
	int alphaBeta(Board& board, int limit, int alpha, int beta);
	int negaScout(Board& board, int limit, int alpha, int beta);

public:
	AIData(BoardStatus color);

	int presearceDepth;
	int normalDepth;
	int perfectDepth;

	bool turn(Board& board);

	BoardStatus color() { return _color; }
};