#pragma once
#include "PlayerData.h"
#include "Board.h"

class Reversi
{
	//�Ֆ�
	Board _board;

	//Player
	PlayerData player[2] = { (Black),(White) };

	bool initial_settings();
	void gameloop();

public:
	void start();
};