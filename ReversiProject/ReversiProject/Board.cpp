#include <iostream>
#include "Board.h"

using namespace std;

Board::Board()
{
}

void Board::init()
{
	_board.clear();

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		//���ڍ\�z�ŐV���ȗv�f�𖖔��ɒǉ�����
		_board.emplace_back();

		for (int j = 0; j < BOARD_SIZE; j++)
		{
			_board[i].push_back(BoardPoint(None, Vector2Int(i, j)));
		}
	}

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		_board[0][i].setStatus(Wall);
		_board[BOARD_SIZE - 1][i].setStatus(Wall);
		_board[i][0].setStatus(Wall);
		_board[i][BOARD_SIZE - 1].setStatus(Wall);
	}

	_board[4][4].setStatus(White);
	_board[5][4].setStatus(Black);
	_board[4][5].setStatus(Black);
	_board[5][5].setStatus(White);
}

void Board::printBoard()
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
				if (_board[i][j].direction() != 0) cout << "�E";
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
			cout << "|";
		}
		cout << endl;
		cout << "-------------------------------" << endl;

	}
}

void Board::placedStone(Vector2Int pos, BoardStatus color)
{
	_board[pos.x][pos.y].setStatus(color);
	reverse(pos, color);
}

void Board::reverse(Vector2Int pos, BoardStatus color)
{
	vector<BoardPoint> updateLog;
	int x, y;

	//�u�����n�_���܂��L�^
	updateLog.push_back(_board[pos.x][pos.y]);

	//�������A�r�b�g�������Ă�n�_�ɒT�����A���]����
	for (int i = 0; i < 8; i++)
	{
		if (!(_board[pos.x][pos.y].direction() & 1 << i))continue;

		x = pos.x + SEARCH_TABLE[i].x;
		y = pos.y + SEARCH_TABLE[i].y;

		while (_board[x][y].status() != color)
		{
			//�΂𔽓]������
			_board[x][y].reverse();
			
			//���̌��ʂ��L�^
			updateLog.push_back(_board[x][y]);

			//����̏ꏊ�ɑJ��
			x += SEARCH_TABLE[i].x;
			y += SEARCH_TABLE[i].y;
		}

	}

	_log.push_back(updateLog);
}

void Board::checkCanPlaced(Vector2Int pos, BoardStatus color)
{
	//���łɒu����Ă�����e��
	if (_board[pos.x][pos.y].status() != BoardStatus::None)return;

	unsigned direction = 0;
	int x, y;
	for (int i = 0; i < 8; i++)
	{
		x = pos.x + SEARCH_TABLE[i].x;
		y = pos.y + SEARCH_TABLE[i].y;

		//�u�����F�̔��]�����F�ȊO�Ȃ�e���Ď���table
		if (_board[x][y].status() != -color)continue;

		//�u�����F�̔��]�����F�������܂ő��s
		while (_board[x][y].status() == -color)
		{
			x += SEARCH_TABLE[i].x;
			y += SEARCH_TABLE[i].y;
		}

		//�Ōオ�����̐F�Ȃ�r�b�g�𗧂Ă�
		if (_board[x][y].status() == color)direction |= (1 << i);
	}

	_board[pos.x][pos.y].setDirection(direction);
}