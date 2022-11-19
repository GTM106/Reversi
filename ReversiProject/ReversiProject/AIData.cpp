#include <iostream>
#include "AIData.h"

using namespace std;

AIData::AIData(BoardStatus color) : _color(color), depth(0)
{
}

bool AIData::turn(Board& board)
{
	for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			board.checkCanPlaced(Vector2Int(i, j), _color);
		}
	}

	//パスに成功したら弾く（置く場所がなかった）
	if (board.pass())
	{
		if (!board.turnEnd())return false;
		return true;
	}

	//思考

	board.resetPassCount();
	if (!board.turnEnd())return false;

	return true;
}