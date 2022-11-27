#include <iostream>
#include <algorithm>
#include <random>

#include "AIData.h"
#include "MidEvaluator.h"
#include "PerfectEvaluator.h"

using namespace std;

AIData::AIData(BoardStatus color) : _color(color), eval(0), normalDepth(5), presearceDepth(3), perfectDepth(13)
{
}

void AIData::put(Board& board)
{
	vector<BoardPoint>& canPlaced = board.CanPlacedPoint();

	int limit = 0;
	evaluator.reset(new MidEvaluator());

	if (64 - board.turn <= perfectDepth)
	{
		limit = INT_MAX;
		evaluator.reset(new PerfectEvaluator());
		cout << "完全読み" << endl;
	}
	else
	{
		limit = normalDepth;
		cout << "通常読み" << endl;
	}

	int eval;
	int alpha = numeric_limits<int>::min();
	int beta = INT_MAX;

	Vector2Int pos;

	for (unsigned i = 0; i < canPlaced.size(); i++)
	{
		board.placedStone(canPlaced[i].position());
		eval = -alphaBeta(board, limit - 1, -beta, -alpha);
		board.undo();
		
		if (eval > alpha)
		{
			alpha = eval;
			pos = canPlaced[i].position();
		}
	}

	board.placedStone(pos);
}

void AIData::random(Board& board)
{
	//乱数生成
	random_device rnd;
	mt19937 mt(rnd());

	vector<BoardPoint> point = board.CanPlacedPoint();
	Vector2Int pos = point[mt() % point.size()].position();

	board.placedStone(pos);
}

int AIData::negaScout(Board& board, int limit, int alpha, int beta)
{
	if (limit == 0)return evaluator->evaluate(board);

	int a = alpha;
	int b = beta;
	int t;
	int scoreMax = -INT_MAX;

	//TODO:可能な手を生成してソート

	for (int i = 0; i < board.CanPlacedPoint().size(); i++)
	{
		board.placedStone(board.CanPlacedPoint()[i].position());
		t = -negaScout(board, limit - 1, -b, -a);

		if (t > a && t < beta && limit>2)
		{
			t = -negaScout(board, limit - 1, -beta, -t);
		}
		board.undo();

		if (t < scoreMax)
		{
			if (t >= beta)return t;
			scoreMax = t;
			a = max(a, t);
		}

		b = a + 1;
	}

	return scoreMax;
}

int AIData::alphaBeta(Board& board, int limit, int alpha, int beta)
{
	if (board.isGameOver() || limit == 0)return evaluator->evaluate(board);

	int score;
	vector<BoardPoint>& canPlaced = board.CanPlacedPoint();

	if (canPlaced.empty())
	{
		board.pass();
		score = -alphaBeta(board, limit, -beta, -alpha);
		board.undo();

		return score;
	}

	for (unsigned i = 0; i < canPlaced.size(); i++)
	{
		board.placedStone(canPlaced[i].position());
		score = -alphaBeta(board, limit - 1, -beta, -alpha);
		board.undo();

		if (score >= beta)return score;

		alpha = max(alpha, score);
	}

	return alpha;
}

bool AIData::turn(Board& board)
{
	//パスに成功したら弾く（置く場所がなかった）
	if (board.pass())
	{
		if (!board.turnEnd())return false;
		return true;
	}

	//1択なら思考はしないで終わる。
	if (board.CanPlacedPoint().size() == 1)
	{
		board.placedStone(board.CanPlacedPoint()[0].position());
	}
	else
	{
		put(board);

		//ランダムに配置
		//random(board);
	}

	board.resetPassCount();
	if (!board.turnEnd())return false;

	return true;
}