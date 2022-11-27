#include "PerfectEvaluator.h"

//Š®‘S“Ç‚Ý‚Ì•]‰¿
int PerfectEvaluator::evaluate(Board& board)
{
	return static_cast<int>(board.currentColor() * (board.colorCount(Black) - board.colorCount(White)));
}