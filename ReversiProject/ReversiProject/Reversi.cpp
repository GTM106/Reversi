#include "Reversi.h"
#include "ConsoleClear.h"
#include <iostream>

using namespace std;

void Reversi::start()
{
	init_board();

	print_board();
	

	//if (!initial_settings())return;

	//gameloop();
}

void Reversi::init_board()
{
	for (int i = 0; i < SIZE; i++)
	{
		//’¼Ú\’z‚ÅV‚½‚È—v‘f‚ð––”ö‚É’Ç‰Á‚·‚é
		_board.emplace_back();

		for (int j = 0; j < SIZE; j++)
		{
			_board[i].push_back(None);
		}
	}

	for (int i = 0; i < SIZE; i++)
	{
		_board[0][i].set_status(Wall);
		_board[SIZE - 1][i].set_status(Wall);
		_board[i][0].set_status(Wall);
		_board[i][SIZE - 1].set_status(Wall);
	}

	_board[4][4].set_status(White);
	_board[5][4].set_status(Black);
	_board[4][5].set_status(Black);
	_board[5][5].set_status(White);
}

void Reversi::print_board()
{
	cout << "-------------------------------" << endl;
	for (int i = 0; i < SIZE; i++)
	{
		cout << "|";
		for (int j = 0; j < SIZE; j++)
		{
			switch (_board[i][j].status())
			{
			case None:
				cout << "@";
				break;
			case White:
				cout << "œ";
				break;
			case Black:
				cout << "›";
				break;
			case Wall:
				cout << "¡";
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