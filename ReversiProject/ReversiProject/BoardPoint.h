#pragma once
#include "Vector2Int.h"

enum BoardStatus
{
	Black = -1,
	None = 0,
	White = 1,
	Wall = 2,

	Max
};

class BoardPoint
{
	Vector2Int _position;

	BoardStatus _status;
	bool _canPlace;
	unsigned _direction;

public:
	BoardPoint(BoardStatus status,Vector2Int pos);

	void reverse();

	Vector2Int position() { return _position; }
	BoardStatus status() { return _status; }
	bool canPlaced() { return _canPlace; }
	unsigned direction() { return _direction; }

	void setStatus(BoardStatus status);
	void setCanPlaced(bool enable);
	void setDirection(unsigned dir);
};

