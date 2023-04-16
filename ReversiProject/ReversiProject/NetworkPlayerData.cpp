#include "NetworkPlayerData.h"

#define PASS -1
#define UNDO -2
#define ESCAPE -3

NetworkPlayerData::NetworkPlayerData(BoardStatus color) : _color(color), _placedPoint(Vector2Int(0, 0))
{
}

bool NetworkPlayerData::networkTurn(Board& board)
{
	if (placedPoint.x == PASS)
	{
		if (board.pass())
		{
			if (!board.turnEnd())return false;
			return true;
		}
	}
	else if (placedPoint.x == UNDO)
	{
		board.undo(_color);

		//�p�X�̔Ֆʂ��i�s�s�\�ɂȂ邩�炻��ȑO�܂Ŗ߂�
		while (board.CanPlacedPoint().empty())
		{
			if (!board.undo(_color))break;

			//2��s���Ď����̃^�[���ɖ߂�
			board.undo(_color);
		}
	}
	else if (placedPoint.x == ESCAPE)return false;

	board.placedStone(placedPoint);

	return false;
}

void NetworkPlayerData::setPlacedPoint(Vector2Int pos)
{
	_placedPoint = pos;
}
