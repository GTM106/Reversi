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
		cout << "黒：" << _board.colorCount(Black) << endl;
		cout << "白：" << _board.colorCount(White) << endl;
		cout << "黒の勝ち" << endl;
	}
	else if (_board.colorCount(Black) < _board.colorCount(White))
	{
		cout << "黒：" << _board.colorCount(Black) << endl;
		cout << "白：" << _board.colorCount(White) << endl;
		cout << "白の勝ち" << endl;
	}
	else
	{
		cout << "黒：" << _board.colorCount(Black) << endl;
		cout << "白：" << _board.colorCount(White) << endl;
		cout << "引き分け" << endl;
	}
	
}