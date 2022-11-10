#include <iostream>
#include <vector>
#include <conio.h>

#include "Reversi.h"
#include "ConsoleManager.h"

using namespace std; 

void Reversi::start()
{
	_board.init();

	if (!initial_settings())return;

	gameloop();
}

bool Reversi::initial_settings()
{
	return true;
}

void Reversi::gameloop()
{
	int turn = 0;
	
	while (true)
	{
		PlayerData p = player[(turn++) % 2];

		p.turn(_board);
	}
}