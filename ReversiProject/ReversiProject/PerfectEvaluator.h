#pragma once
#include "Evaluator.h"

class PerfectEvaluator :public Evaluator
{
public:
	int evaluate(Board& board);
};