#include <iostream>
#include <vector>
#include <conio.h>

#include "Reversi.h"
#include "ConsoleManager.h"
#include "PlayerData.h"

using namespace std; 

void Reversi::start()
{
	init_board();

	if (!initial_settings())return;

	gameloop();
}

void Reversi::init_board()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		//直接構築で新たな要素を末尾に追加する
		_board.emplace_back();

		for (int j = 0; j < BOARD_SIZE; j++)
		{
			_board[i].push_back(None);
		}
	}

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		_board[0][i].set_status(Wall);
		_board[BOARD_SIZE - 1][i].set_status(Wall);
		_board[i][0].set_status(Wall);
		_board[i][BOARD_SIZE - 1].set_status(Wall);
	}

	_board[4][4].set_status(White);
	_board[5][4].set_status(Black);
	_board[4][5].set_status(Black);
	_board[5][5].set_status(White);
}

void Reversi::print_board()
{
	cout << "-------------------------------" << endl;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		cout << "|";
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			switch (_board[i][j].status())
			{
			case None:
				if (_board[i][j].can_placed()) cout << "・";
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
			cout << "|";
		}
		cout << endl;
		cout << "-------------------------------" << endl;
	}
}

bool Reversi::initial_settings()
{
	return true;
}

void Reversi::gameloop()
{
	ConsoleManager consoleManager;

	int turn = 0;
	while (true)
	{
		PlayerData p = player[(turn++) % 2];

		//表示
		rewrite_can_placed_board(p.color());
		consoleManager.console_clear();
		print_board();

		p.turn(_board);
	}
}

void Reversi::rewrite_can_placed_board(BoardStatus color)
{
	BoardStatus reverseColor = color == Black ? White : Black;

	vector<vector<int>> search_table = { {0,1},{0,-1},{1,0},{-1,0},{1,1},{1,-1} ,{-1,1},{-1,-1} };

	//全探索。より良い方法模索中
	for (int i = 1; i < BOARD_SIZE - 1; i++)
	{
		for (int j = 1; j < BOARD_SIZE - 1; j++)
		{
			//すでに置かれていたら置けない
			if (_board[i][j].status() != None)
			{
				_board[i][j].set_can_placed(false);
				continue;
			}

			//置かれていない場所なら八方向に探索
			for (int k = 0; k < 8; k++)
			{
				//depthを使うならこの処理をやめてdepthによって判定
				bool can_placed = linear_search(0, i, j, search_table[k][0], search_table[k][1], color);
				_board[i][j].set_can_placed(can_placed);
				if (can_placed)break;
			}
		}
	}
}

bool Reversi::linear_search(int depth, int i, int j, int iplus, int jplus, BoardStatus color)
{
	BoardStatus current_board_status = _board[i + iplus][j + jplus].status();

	//どの場合でも、置かれていない場合と壁の場合は探索失敗
	if (current_board_status == None)return false;
	if (current_board_status == Wall)return false;

	//自分の色で初探索なら探索失敗、二回目以降は探索成功
	if (current_board_status == color)return depth != 0;

	//自分でない色の場合探索続行
	return linear_search(++depth, i + iplus, j + jplus, iplus, jplus, color);
}
