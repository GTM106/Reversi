#pragma once
#include "Board.h"

class INetworkTurn
{
public:
	//Network‚ÅŽg—p
	Vector2Int placedPoint;
	virtual ~INetworkTurn() {}
	virtual	bool networkTurn(Board& board) = 0;
};
