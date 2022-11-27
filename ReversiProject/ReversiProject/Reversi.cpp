#include <iostream>
#include <vector>
#include <conio.h>

#include "Reversi.h"
#include "ConsoleManager.h"

using namespace std;

void Reversi::start()
{
	if (!initial_settings())return;

	gameloop();
}

bool Reversi::initial_settings()
{
	player[0].reset(new PlayerData(Black));
	player[1].reset(new AIData(White));

	return true;
}

void Reversi::gameloop()
{
	int turn = 0;

	while (true)
	{
		if (!player[(turn++) % 2]->turn(_board))break;
	}

	if (_board.colorCount(Black) > _board.colorCount(White))
	{
		cout << "���F" << _board.colorCount(Black) << endl;
		cout << "���F" << _board.colorCount(White) << endl;
		cout << "���̏���" << endl;
	}
	else if (_board.colorCount(Black) < _board.colorCount(White))
	{
		cout << "���F" << _board.colorCount(Black) << endl;
		cout << "���F" << _board.colorCount(White) << endl;
		cout << "���̏���" << endl;
	}
	else
	{
		cout << "���F" << _board.colorCount(Black) << endl;
		cout << "���F" << _board.colorCount(White) << endl;
		cout << "��������" << endl;
	}
	
}