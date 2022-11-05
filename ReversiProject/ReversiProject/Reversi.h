#pragma once
#include "Board.h"
#include <vector>

class Reversi
{
	const int SIZE = 10;

	//”Õ–Ê
	std::vector<std::vector<Board>> _board = {};
	
	void init_board();
	bool initial_settings();
	void print_board();
	void gameloop();
		
public:
	void start();
};

