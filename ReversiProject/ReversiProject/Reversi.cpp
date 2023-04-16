#include <iostream>
#include <vector>
#include <conio.h>

#include "Reversi.h"
#include "ConsoleManager.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_2 50
#define KEY_4 52
#define KEY_6 54
#define KEY_8 56
#define KEY_U 117
#define KEY_TAB 9
#define KEY_ESC 27

using namespace std;

void Reversi::start()
{
	ConsoleManager consoleManager;

	consoleManager.setConsoleCursorErase();

	while (true)
	{
		if (!initial_settings())return;

		gameloop();
		gameFinish();

		if (!isContinue())break;
	}
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

	_board.init();

	while (true)
	{
		if (!player[(turn++) % 2]->turn(_board))break;
	}
}

void Reversi::gameFinish()
{
	ConsoleManager manager;

	manager.setColor(COL_CYAN);
	cout << endl << "　☆結果発表☆　" << endl;

	manager.setColor(COL_WHITE);
	cout << "黒：" << _board.colorCount(Black) << endl;
	cout << "白：" << _board.colorCount(White) << endl;

	if (_board.colorCount(Black) > _board.colorCount(White))
	{
		cout << "黒の勝ち" << endl;
	}
	else if (_board.colorCount(Black) < _board.colorCount(White))
	{
		cout << "白の勝ち" << endl;
	}
	else
	{
		cout << "引き分け" << endl;
	}

	manager.resetConsoleColor();
}

bool Reversi::isContinue()
{
	bool isContinue = true;

	//棄却もどき。プレイヤーの入力待ち
	int _ = _getch();

	ConsoleManager consoleManager;

	auto print = [](ConsoleManager consoleManager,bool isContinue)
	{
		consoleManager.console_clear();

		consoleManager.setColor(COL_YELLOW);
		cout << "アプリケーションを終了しますか？" << endl;
		if (!isContinue)
		{
			consoleManager.setColor(COL_RED);
			cout << "→";
		}
		cout << "　　はい" << endl;
		if (isContinue)cout << "→";
		consoleManager.setColor(COL_YELLOW);
		cout << "　　いいえ" << endl;
		consoleManager.resetConsoleColor();
	};

	print(consoleManager, isContinue);

	int val = 0;
	while (val != KEY_ENTER)
	{
		switch ((val = _getch()))
		{
			//上
		case KEY_8:
		case KEY_W:
		case KEY_UP:
			if (!isContinue)continue;
			isContinue = false;
			break;
			//下
		case KEY_2:
		case KEY_S:
		case KEY_DOWN:
			if (isContinue)continue;
			isContinue = true;
			break;
			//決定
		case KEY_ENTER:
			return isContinue;
		case KEY_ESC:
			return true;
		default:
			continue;
		}

		print(consoleManager, isContinue);
	}

	return false;
}