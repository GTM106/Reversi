#include <iostream>
#include <vector>
#include <conio.h>

#include "PlayerData.h"
#include "ConsoleManager.h"
#include "Vector2Int.h"

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

using namespace std;

PlayerData::PlayerData(BoardStatus color) : _color(color)
{
}

bool PlayerData::turn(Board& board)
{
	//パスに成功したら弾く（置く場所がなかった）
	if (board.pass())
	{
		if (!board.turnEnd())return false;
		return true;
	}

	input(board);

	board.resetPassCount();
	if (!board.turnEnd())return false;

	return true;
}

void PlayerData::input(Board& board)
{
	ConsoleManager consoleManager;

	int h = 5;
	int v = 5;

	//現在の地点を特殊表示
	consoleManager.console_clear();
	print_board(h, v, board);

	//入力
	int val = 0;
	while (val != KEY_ENTER)
	{
		switch ((val = _getch()))
		{
		//上
		case KEY_8:
		case KEY_W:
		case KEY_UP:
			if (v == 1)	continue;
			v--;

			break;
		//下
		case KEY_2:
		case KEY_S:
		case KEY_DOWN:
			if (v == static_cast<int>(board.board().size() - 2))continue;
			v++;

			break;
		//左
		case KEY_4:
		case KEY_A:
		case KEY_LEFT:
			if (h == 1)continue;
			h--;

			break;
		//右
		case KEY_6:
		case KEY_D:
		case KEY_RIGHT:
			if (h == static_cast<int>(board.board().size() - 2))continue;
			h++;

			break;
		//決定
		case KEY_ENTER:
			if (board.board()[v][h].direction() == 0)
			{
				val = 0;
				cout << "そこには置けません。" << endl;
				continue;
			}

			board.placedStone(Vector2Int(v, h));
			break;
		//Undo
		case KEY_U:
			if (!board.undo(_color))
			{
				cout << "それ以上戻せません" << endl;
				continue;
			}

			//2回行って自分のターンに戻る
			board.undo(_color);

			//パスの盤面が進行不能になるからそれ以前まで戻す
			while (board.CanPlacedPoint().empty())
			{
				if (!board.undo(_color))
				{
					break;
				}

				//2回行って自分のターンに戻る
				board.undo(_color);
			}

			break;

		default:
			continue;
		}

		//現在の地点を特殊表示
		consoleManager.console_clear();
		print_board(h, v, board);
	}
}

//通常とは異なる特殊な盤面表示
void PlayerData::print_board(int h, int v, Board _board)
{
	ConsoleManager consoleManager;

	auto& board = _board.board();

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
				if (_board.board()[i][j].direction() != 0) cout << "・";
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