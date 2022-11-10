#pragma once
#include <vector>
#include "Vector2Int.h"
#include "BoardPoint.h"

class Board
{
	const int BOARD_SIZE = 10;

	//10*10�̔ՖʁAvector�ł���K�v�͂Ȃ��������₷�����߂���Œ�`
	std::vector<std::vector<BoardPoint>> _board;

	//���̃^�[���N�������̕ۑ��B
	std::vector<std::vector<BoardPoint>> _log;

	const Vector2Int SEARCH_TABLE[8] = { Vector2Int(0,-1),Vector2Int(1,-1),Vector2Int(1,0),Vector2Int(1,1),Vector2Int(0,1),Vector2Int(-1,1) ,Vector2Int(-1,0),Vector2Int(-1,-1) };

	void reverse(Vector2Int pos,BoardStatus color);

public:
	Board();
	void checkCanPlaced(const Vector2Int pos, BoardStatus color);

	void init();
	void undo();
	void pass();
	void placedStone(Vector2Int pos,BoardStatus color);

	void printBoard();

	std::vector<std::vector<BoardPoint>>& board() { return _board; }
};