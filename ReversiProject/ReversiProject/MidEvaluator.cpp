#include "MidEvaluator.h"

//静的メンバ変数は実体を別に宣言する必要がある。
bool MidEvaluator::TableInit;
MidEvaluator::EdgeStorage MidEvaluator::EdgeTable[TABLE_SIZE];

MidEvaluator::MidEvaluator()
{
	if (!TableInit)
	{
		BoardStatus line[8];
		generateEdge(line, 0);

		TableInit = true;
	}

	EvalWeight.mobility_w = 67;
	EvalWeight.liberty_w = -13;
	EvalWeight.stable_w = 101;
	EvalWeight.wing_w = -308;
	EvalWeight.Xput_w = -449;
	EvalWeight.Cput_w = -552;
}


int MidEvaluator::evaluate(Board& board)
{
	MidEvaluator::EdgeParameter edgeParam[3];
	MidEvaluator::CornerStorage cornerStorage;
	int result;

	//辺の評価
	for (int i = 0; i < 3; i++)
	{
		edgeParam[i] = EdgeTable[idxTop(board)][i];
		edgeParam[i] += EdgeTable[idxButtom(board)][i];
		edgeParam[i] += EdgeTable[idxRight(board)][i];
		edgeParam[i] += EdgeTable[idxLeft(board)][i];
	}

	//隅の評価
	cornerStorage = evalCorner(board);

	//重複を補正
	edgeParam[Black + 1].stable -= cornerStorage[Black + 1].corner;
	edgeParam[White + 1].stable -= cornerStorage[White + 1].corner;

	result = edgeParam[Black + 1].stable * EvalWeight.stable_w - edgeParam[White + 1].stable * EvalWeight.stable_w
		+ edgeParam[Black + 1].wing * EvalWeight.wing_w - edgeParam[White + 1].wing * EvalWeight.wing_w
		+ cornerStorage[Black + 1].Xput * EvalWeight.Xput_w - cornerStorage[White + 1].Xput * EvalWeight.Xput_w
		+ edgeParam[Black + 1].Cput * EvalWeight.Cput_w - edgeParam[White + 1].Cput * EvalWeight.Cput_w;

	result += board.currentColor() * static_cast<int>(board.CanPlacedPoint().size()) * EvalWeight.mobility_w;

	return board.currentColor() * result;
}

void MidEvaluator::generateEdge(BoardStatus edge[], unsigned count)
{
	if (count == 8)
	{
		EdgeParameter edgeParam[3];

		edgeParam[Black + 1] = evalEdge(edge, Black);
		edgeParam[White + 1] = evalEdge(edge, White);

		EdgeTable[idxLine(edge)][Black + 1] = edgeParam[Black + 1];
		EdgeTable[idxLine(edge)][White + 1] = edgeParam[White + 1];

		return;
	}

	edge[count] = None;
	generateEdge(edge, count + 1);

	edge[count] = Black;
	generateEdge(edge, count + 1);

	edge[count] = White;
	generateEdge(edge, count + 1);
}

MidEvaluator::EdgeParameter MidEvaluator::evalEdge(BoardStatus line[], BoardStatus color) const
{
	EdgeParameter edgeParam = { 0,0,0,0 };

	unsigned x;

	if (line[0] == None && line[7] == None)
	{
		x = 2;
		while (x <= 5)
		{
			if (line[x] != color)break;
			x++;
		}
		if (x == 6)
		{
			if (line[1] == color && line[6] == None)edgeParam.wing = 1;
			else if (line[1] == None && line[6] == color)edgeParam.wing = 1;
			else if (line[1] == color && line[6] == color)edgeParam.mountain = 1;
		}
		else
		{
			if (line[1] == color)edgeParam.Cput++;
			if (line[6] == color)edgeParam.Cput++;
		}
	}

	for (x = 0; x < 8; x++)
	{
		if (line[x] != color)break;
		edgeParam.stable++;
	}

	if (edgeParam.stable < 8)
	{
		for (x = 7; x > 0; x--)
		{
			if (line[x] != color)break;
			edgeParam.stable++;
		}
	}
	return edgeParam;
}

MidEvaluator::CornerStorage MidEvaluator::evalCorner(Board& board)
{
	CornerStorage cornerParam;

	Vector2Int pos[4] = { Vector2Int(1,1),Vector2Int(1,8),Vector2Int(8,8), Vector2Int(8,1) };
	Vector2Int pos2[4] = { Vector2Int(2,2),Vector2Int(2,7),Vector2Int(7,7), Vector2Int(7,2) };

	cornerParam[static_cast<int>(Black)].corner = 0;
	cornerParam[static_cast<int>(Black)].Xput = 0;
	cornerParam[static_cast<int>(White)].corner = 0;
	cornerParam[static_cast<int>(White)].Xput = 0;

	for (int i = 0; i < 4; i++)
	{
		cornerParam[board.board()[pos->x][pos->y].status()].corner++;
		if (board.board()[pos->x][pos->y].status() == None)cornerParam[board.board()[pos2->x][pos2->y].status()].Xput++;
	}

	return cornerParam;
}

inline unsigned MidEvaluator::idxTop(Board& board)
{
	return 2187 * (board.board()[1][1].status() + 1)
		+ 729 * (board.board()[2][1].status() + 1)
		+ 243 * (board.board()[3][1].status() + 1)
		+ 81 * (board.board()[4][1].status() + 1)
		+ 27 * (board.board()[5][1].status() + 1)
		+ 9 * (board.board()[6][1].status() + 1)
		+ 3 * (board.board()[7][1].status() + 1)
		+ 1 * (board.board()[8][1].status() + 1)
		;
}

inline unsigned MidEvaluator::idxButtom(Board& board)
{
	return 2187 * (board.board()[1][1].status() + 1)
		+ 729 * (board.board()[1][2].status() + 1)
		+ 243 * (board.board()[1][3].status() + 1)
		+ 81 * (board.board()[1][4].status() + 1)
		+ 27 * (board.board()[1][5].status() + 1)
		+ 9 * (board.board()[1][6].status() + 1)
		+ 3 * (board.board()[1][7].status() + 1)
		+ 1 * (board.board()[1][8].status() + 1)
		;
}

inline unsigned MidEvaluator::idxRight(Board& board)
{
	return 2187 * (board.board()[8][1].status() + 1)
		+ 729 * (board.board()[8][2].status() + 1)
		+ 243 * (board.board()[8][3].status() + 1)
		+ 81 * (board.board()[8][4].status() + 1)
		+ 27 * (board.board()[8][5].status() + 1)
		+ 9 * (board.board()[8][6].status() + 1)
		+ 3 * (board.board()[8][7].status() + 1)
		+ 1 * (board.board()[8][8].status() + 1)
		;
}

inline unsigned MidEvaluator::idxLeft(Board& board)
{
	return 2187 * (board.board()[1][8].status() + 1)
		+ 729 * (board.board()[2][8].status() + 1)
		+ 243 * (board.board()[3][8].status() + 1)
		+ 81 * (board.board()[4][8].status() + 1)
		+ 27 * (board.board()[5][8].status() + 1)
		+ 9 * (board.board()[6][8].status() + 1)
		+ 3 * (board.board()[7][8].status() + 1)
		+ 1 * (board.board()[8][8].status() + 1)
		;
}