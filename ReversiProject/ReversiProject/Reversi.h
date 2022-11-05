#pragma once
#include "Board.h"
#include "PlayerData.h"
#include <vector>

class Reversi
{
	const int SIZE = 10;

	//”Õ–Ê
	std::vector<std::vector<Board>> _board = {};

	//Player
	PlayerData player[2] = { (Black),(White) };

	void init_board();
	bool initial_settings();
	void print_board();
	void gameloop();
	void rewrite_can_placed_board(BoardStatus color);
	bool linear_search(int depth, int i, int j, int ipuls, int jpuls, BoardStatus color);

public:
	void start();
};