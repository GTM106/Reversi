#include <iostream>
#include <vector>
#include <conio.h>

#include "PlayerData.h"
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

using namespace std;

PlayerData::PlayerData(BoardStatus color)
{
	_color = color;
}

void PlayerData::turn(vector<vector<Board>>& board)
{
	input(board);
}

void PlayerData::input(vector<vector<Board>>& board)
{
	ConsoleManager consoleManager;

	int h = 5;
	int v = 5;

	//入力
	int val = 0;
	while (val != KEY_ENTER)
	{
		switch ((val = _getch()))
		{
		case KEY_8:
		case KEY_W:
		case KEY_UP:
			if (--v == 0)v = 1;
			break;

		case KEY_2:
		case KEY_S:
		case KEY_DOWN:
			if (++v == static_cast<int>(board.size() - 1))v = static_cast<int>(board.size() - 2);
			break;

		case KEY_4:
		case KEY_A:
		case KEY_LEFT:
			if (--h == 0)h = 1;
			break;

		case KEY_6:
		case KEY_D:
		case KEY_RIGHT:
			if (++h == static_cast<int>(board.size() - 1))h = static_cast<int>(board.size() - 2);
			break;
		case KEY_ENTER:
			if (!board[v][h].can_placed())
			{
				val = 0;
				cout << "そこには置けません。" << endl;
				continue;
			}

			board[v][h].set_status(_color);
			break;
		default:
			break;
		}

		//現在の地点を特殊表示
		consoleManager.console_clear();
		print_board(h, v, board);
	}
}

//通常とは異なる特殊な盤面表示
void PlayerData::print_board(int h, int v, vector<vector<Board>> board)
{
	ConsoleManager consoleManager;

	cout << "-------------------------------" << endl;
	for (int i = 0; i < board.size(); i++)
	{
		cout << "|";
		for (int j = 0; j < board.size(); j++)
		{
			if (h == j && v == i)consoleManager.setConsoleBackGray();

			switch (board[i][j].status())
			{
			case None:
				if (board[i][j].can_placed()) cout << "・";
				else cout << "　";
				break;
			case White:
				cout << "●";
				break;
			case Black:
				cout << "○";
				break;
			case Wall:
				cout << "■";
				break;
			default:
				break;
			}

			if (h == j && v == i)consoleManager.setConsoleBackBlack();

			cout << "|";
		}
		cout << endl;
		cout << "-------------------------------" << endl;
	}
}