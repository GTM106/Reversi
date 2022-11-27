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
	//�p�X�ɐ���������e���i�u���ꏊ���Ȃ������j
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

	//���݂̒n�_�����\��
	consoleManager.console_clear();
	print_board(h, v, board);

	//����
	int val = 0;
	while (val != KEY_ENTER)
	{
		switch ((val = _getch()))
		{
		//��
		case KEY_8:
		case KEY_W:
		case KEY_UP:
			if (v == 1)	continue;
			v--;

			break;
		//��
		case KEY_2:
		case KEY_S:
		case KEY_DOWN:
			if (v == static_cast<int>(board.board().size() - 2))continue;
			v++;

			break;
		//��
		case KEY_4:
		case KEY_A:
		case KEY_LEFT:
			if (h == 1)continue;
			h--;

			break;
		//�E
		case KEY_6:
		case KEY_D:
		case KEY_RIGHT:
			if (h == static_cast<int>(board.board().size() - 2))continue;
			h++;

			break;
		//����
		case KEY_ENTER:
			if (board.board()[v][h].direction() == 0)
			{
				val = 0;
				cout << "�����ɂ͒u���܂���B" << endl;
				continue;
			}

			board.placedStone(Vector2Int(v, h));
			break;
		//Undo
		case KEY_U:
			if (!board.undo(_color))
			{
				cout << "����ȏ�߂��܂���" << endl;
				continue;
			}

			//2��s���Ď����̃^�[���ɖ߂�
			board.undo(_color);

			//�p�X�̔Ֆʂ��i�s�s�\�ɂȂ邩�炻��ȑO�܂Ŗ߂�
			while (board.CanPlacedPoint().empty())
			{
				if (!board.undo(_color))
				{
					break;
				}

				//2��s���Ď����̃^�[���ɖ߂�
				board.undo(_color);
			}

			break;

		default:
			continue;
		}

		//���݂̒n�_�����\��
		consoleManager.console_clear();
		print_board(h, v, board);
	}
}

//�ʏ�Ƃ͈قȂ����ȔՖʕ\��
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
				if (_board.board()[i][j].direction() != 0) cout << "�E";
				else cout << "�@";
				break;
			case White:
				cout << "��";
				break;
			case Black:
				cout << "��";
				break;
			case Wall:
				cout << "��";
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