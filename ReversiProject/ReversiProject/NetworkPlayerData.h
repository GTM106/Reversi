#pragma once
#include "INetworkTurn.h"
#include "Vector2Int.h"
#include "BoardPoint.h"

class NetworkPlayerData:public INetworkTurn
{
	Vector2Int _placedPoint;

	BoardStatus _color;

public:
	NetworkPlayerData(BoardStatus color);

	// INetworkTurn ����Čp������܂���
	virtual bool networkTurn(Board& board) override;
	void setPlacedPoint(Vector2Int pos);
};
