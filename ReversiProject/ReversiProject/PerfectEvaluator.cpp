#include "PerfectEvaluator.h"

//���S�ǂ݂̕]��
int PerfectEvaluator::evaluate(Board& board)
{
	return static_cast<int>(board.currentColor() * (board.colorCount(Black) - board.colorCount(White)));
}