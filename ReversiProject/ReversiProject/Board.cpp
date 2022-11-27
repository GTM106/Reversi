#include <iostream>
#include "Board.h"

using namespace std;

Board::Board() :_passCount(0), turn(0)
{
	//�����ΐ�
	_colorCount[static_cast<int>(Black)] = 2;
	_colorCount[static_cast<int>(None)] = 60;
	_colorCount[static_cast<int>(White)] = 2;

	//�Ֆʂ̏�����
	init();
}

void Board::init()
{
	_board.clear();
	_log.clear();

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

	initCanPlacedPoint();
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
				if (CanPlacedPoint()[turn].direction() != 0) cout << "�E";
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

void Board::placedStone(const Vector2Int pos)
{
	_board[pos.x][pos.y].setStatus(_currentColor);

	_colorCount[static_cast<int>(_currentColor)]++;
	_colorCount[static_cast<int>(None)]--;

	reverse(pos, _currentColor);
	
	turn++;
	_currentColor = static_cast<BoardStatus>(-_currentColor);

	initCanPlacedPoint();
}

void Board::reverse(const Vector2Int pos, const BoardStatus color)
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

			//�΂̑�����ۑ�
			_colorCount[static_cast<int>(color)]++;
			_colorCount[static_cast<int>(-color)]--;

			//���̌��ʂ��L�^
			updateLog.push_back(_board[x][y]);

			//����̏ꏊ�ɑJ��
			x += SEARCH_TABLE[i].x;
			y += SEARCH_TABLE[i].y;
		}
	}

	//����̃��O��ۑ�
	_log.push_back(updateLog);
}

void Board::initCanPlacedPoint()
{
	_canPlacedPoint[turn].clear();

	for (int i = 1; i < 9; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			checkCanPlaced(Vector2Int(i, j), _currentColor);

			if (_board[i][j].direction() != 0)
			{
				_canPlacedPoint[turn].emplace_back(_board[i][j]);
			}
		}
	}
}

void Board::checkCanPlaced(const Vector2Int pos, const BoardStatus color)
{
	//���łɒu����Ă�����e��
	if (_board[pos.x][pos.y].status() != BoardStatus::None)
	{
		_board[pos.x][pos.y].setDirection(0);
		_board[pos.x][pos.y].resetReverseCount();
		return;
	}

	//���]�ł���������Z�b�g
	_board[pos.x][pos.y].resetReverseCount();

	unsigned direction = 0;
	unsigned reverseCount = 0;
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
			reverseCount++;
		}

		//�Ōオ�����̐F�Ȃ�r�b�g�𗧂Ă�
		if (_board[x][y].status() == color)
		{
			direction |= (1 << i);
			_board[pos.x][pos.y].addReverseCount(reverseCount);
		}
		else reverseCount = 0;
	}

	_board[pos.x][pos.y].setDirection(direction);

	//�u����ꏊ������Ȃ�u����ꏊ�̒n�_�ɓo�^
	//if (direction != 0)	_canPlacedPoint[turn].push_back(_board[pos.x][pos.y]);
}

bool Board::undo(BoardStatus color)
{
	//���̂Ƃ��ƍ��̂Ƃ��Ŗ߂�����E�l���Ⴄ
	int limit = color == Black ? 0 : 1;
	if (_log.size() <= limit)return false;

	//���߂����߁A���݂̐F�𔽓]������
	_currentColor = static_cast<BoardStatus>(-_currentColor);

	//�ŐV�̏��͌��ɂ���
	vector<BoardPoint>& latestInfo = _log.back();

	//��񂪂Ȃ�������p�X�����^�[��
	if (latestInfo.empty())
	{
		//������Ƃɖ߂������O���폜
		_log.pop_back();

		return true;
	}

	//�ł����n�_��undo
	Vector2Int pos = latestInfo[0].position();
	_board[pos.x][pos.y].setStatus(None);

	//�΂̑�����ۑ�
	_colorCount[static_cast<int>(latestInfo[0].status())]--;
	_colorCount[static_cast<int>(None)]++;

	//reverse�����n�_��undo
	for (int i = 1; i < latestInfo.size(); i++)
	{
		pos = latestInfo[i].position();
		_board[pos.x][pos.y].reverse();

		//�΂̑�����ۑ�
		_colorCount[static_cast<int>(latestInfo[i].status())]--;
		_colorCount[static_cast<int>(-latestInfo[i].status())]++;
	}

	//������Ƃɖ߂������O���폜
	_log.pop_back();

	//�^�[����߂�
	turn--;
	initCanPlacedPoint();

	return true;
}

bool Board::undo()
{
	return undo(_currentColor);
}

bool Board::pass()
{
	if (_canPlacedPoint[turn].size() > 0)return false;

	//��̔z�����
	_log.push_back(vector<BoardPoint>());

	//�p�X�񐔂��L�^�B�A��2��ŃQ�[���I��
	_passCount++;

	_currentColor = static_cast<BoardStatus>(-_currentColor);

	initCanPlacedPoint();

	return true;
}

bool Board::turnEnd()
{
	if (isGameOver())return false;

	return true;
}

bool Board::isGameOver()
{
	if (_passCount >= 2)return true;
	if (_colorCount[static_cast<int>(None)] == 0)return true;

	return false;
}

void Board::resetPassCount()
{
	_passCount = 0;
}

void Board::reverseCurrentColor()
{
	_currentColor = static_cast<BoardStatus>(-_currentColor);
}