#pragma once
#include <memory>

#include "PlayerData.h"
#include "AIData.h"
#include "Board.h"

class Reversi
{
	//”Õ–Ê
	Board _board;

	//Player
	std::unique_ptr<ITurn> player[2];

	bool initial_settings();
	void gameloop();
	void gameFinish();

public:
	void start();
};