#pragma once
#include <iostream>
#include <WinSock2.h>
#include <string>
#include "INetworkTurn.h"
#include "Board.h"

enum NetworkStatus
{
	Host,
	Client,
};

class NetworkReversi
{
	Board _board;
	NetworkStatus _status;

	std::unique_ptr<INetworkTurn> player[2];

	void init();

public:
	NetworkReversi(NetworkStatus status);
	~NetworkReversi();

	Vector2Int playerTurn(NetworkStatus status);
	void enemyTurn(NetworkStatus status, std::string posData);
};