#pragma once
#include "Board.h"
class Evaluator
{
public:
	virtual int evaluate(Board& board) = 0;
};

