#include <iostream>
#include <vector>
#include <conio.h>

#include "PlayerData.h"
#include "Vector2Int.h"
#include "ForcedTerminationException.h"

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

	try
	{
		input(board);
	}
	catch(ForcedTerminationException)//�����I���I���������m������I��������
	{
		cout << "�c�c�Q�[�����I�����܂��B" << endl;
		return false;
	}
	
	board.resetPassCount();
	if (!board.turnEnd())return false;

	return true;
}

void PlayerData::input(Board& board)
{
	int h = 5;
	int v = 5;

	//���݂̒n�_�����\��
	print_board(h, v, board);

	bool isPrintOperationExplanation = false;

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
				_consoleManager.setColor(COL_RED);
				cout << "�����ɂ͒u���܂���B" << endl;
				_consoleManager.resetConsoleColor();
				continue;
			}

			board.placedStone(Vector2Int(v, h));
			break;
			//Undo
		case KEY_U:
			if (!board.undo(_color))
			{
				_consoleManager.setColor(COL_RED);
				cout << "����ȏ�߂��܂���" << endl;
				_consoleManager.resetConsoleColor();
				continue;
			}

			//2��s���Ď����̃^�[���ɖ߂�
			board.undo(_color);

			//�p�X�̔Ֆʂ��i�s�s�\�ɂȂ邩�炻��ȑO�܂Ŗ߂�
			while (board.CanPlacedPoint().empty())
			{
				if (!board.undo(_color))break;
				
				//2��s���Ď����̃^�[���ɖ߂�
				board.undo(_color);
			}

			break;

		case KEY_TAB:
			isPrintOperationExplanation ^= true;
			break;
		case KEY_ESC:
			if (isFinishGame(h, v, board))throw ForcedTerminationException();//���S�ɋ����I��������
			break;
		default:
			continue;
		}

		//���݂̒n�_�����\��
		print_board(h, v, board);
		if (isPrintOperationExplanation)operationExplanation();
	}
}

void PlayerData::operationExplanation()
{
	_consoleManager.setColor(COL_CYAN);
	cout << "�@�� ������� ���@" << endl;
	cout << "[�ړ�] �@�@  WASD�E�e���L�[�E���L�[" << endl;
	cout << "[��蒼��]�@ U" << endl;
	cout << "[�΂�ł�]�@ ENTER" << endl;
	cout << "[����]�@�@ TAB" << endl;
	cout << "[�Q�[���I��] ESC" << endl;
	_consoleManager.resetConsoleColor();
}

bool PlayerData::isFinishGame(int h, int v, Board board)
{
	bool isFinish = false;

	print_board(h, v, board);
	_consoleManager.setColor(COL_YELLOW);
	cout << "�Q�[�����I�����܂����H" << endl;
	if (isFinish)cout << "��";
	cout << "�@�@�͂�" << endl;
	if (!isFinish)cout << "��";
	cout << "�@�@������" << endl;

	_consoleManager.resetConsoleColor();

	int val = 0;
	while (val != KEY_ENTER)
	{
		switch ((val = _getch()))
		{
			//��
		case KEY_8:
		case KEY_W:
		case KEY_UP:
			if (isFinish)continue;
			isFinish = true;
			break;
			//��
		case KEY_2:
		case KEY_S:
		case KEY_DOWN:
			if (!isFinish)continue;
			isFinish = false;
			break;
			//����
		case KEY_ENTER:
			return isFinish;
		case KEY_ESC:
			return false;
		default:
			continue;
		}

		print_board(h, v, board);
		_consoleManager.setColor(COL_YELLOW);
		cout << "�Q�[�����I�����܂����H" << endl;
		if (isFinish)cout << "��";
		cout << "�@�@�͂�" << endl;
		if (!isFinish)cout << "��";
		cout << "�@�@������" << endl;
		_consoleManager.resetConsoleColor();
	}

	return false;
}

//�ʏ�Ƃ͈قȂ����ȔՖʕ\��
void PlayerData::print_board(int h, int v, Board _board)
{
	//�R���\�[���̃N���A
	_consoleManager.console_clear();

	//��������\���̃w���v
	_consoleManager.setColor(COL_CYAN);
	cout << endl << endl << "TAB�L�[�������đ��������\���c" << endl;
	_consoleManager.resetConsoleColor();

	auto& board = _board.board();

	cout << "-------------------------------" << endl;
	for (int i = 0; i < board.size(); i++)
	{
		cout << "|";
		for (int j = 0; j < board.size(); j++)
		{
			if (h == j && v == i)_consoleManager.setConsoleBackGray();

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

			if (h == j && v == i)_consoleManager.resetConsoleColor();

			cout << "|";
		}
		cout << endl;
		cout << "-------------------------------" << endl;
	}
}