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
	cout << endl << "�@�����ʔ��\���@" << endl;

	manager.setColor(COL_WHITE);
	cout << "���F" << _board.colorCount(Black) << endl;
	cout << "���F" << _board.colorCount(White) << endl;

	if (_board.colorCount(Black) > _board.colorCount(White))
	{
		cout << "���̏���" << endl;
	}
	else if (_board.colorCount(Black) < _board.colorCount(White))
	{
		cout << "���̏���" << endl;
	}
	else
	{
		cout << "��������" << endl;
	}

	manager.resetConsoleColor();
}

bool Reversi::isContinue()
{
	bool isContinue = true;

	//���p���ǂ��B�v���C���[�̓��͑҂�
	int _ = _getch();

	ConsoleManager consoleManager;

	auto print = [](ConsoleManager consoleManager,bool isContinue)
	{
		consoleManager.console_clear();

		consoleManager.setColor(COL_YELLOW);
		cout << "�A�v���P�[�V�������I�����܂����H" << endl;
		if (!isContinue)
		{
			consoleManager.setColor(COL_RED);
			cout << "��";
		}
		cout << "�@�@�͂�" << endl;
		if (isContinue)cout << "��";
		consoleManager.setColor(COL_YELLOW);
		cout << "�@�@������" << endl;
		consoleManager.resetConsoleColor();
	};

	print(consoleManager, isContinue);

	int val = 0;
	while (val != KEY_ENTER)
	{
		switch ((val = _getch()))
		{
			//��
		case KEY_8:
		case KEY_W:
		case KEY_UP:
			if (!isContinue)continue;
			isContinue = false;
			break;
			//��
		case KEY_2:
		case KEY_S:
		case KEY_DOWN:
			if (isContinue)continue;
			isContinue = true;
			break;
			//����
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