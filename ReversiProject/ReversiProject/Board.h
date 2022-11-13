#pragma once
#include <vector>
#include "Vector2Int.h"
#include "BoardPoint.h"

class Board
{
	const int BOARD_SIZE = 10;
	const int BOARD_MAX = 64;

	//10*10の盤面、vectorである必要はないが扱いやすいためこれで定義
	std::vector<std::vector<BoardPoint>> _board;

	//そのターン置ける場所
	std::vector<BoardPoint> _canPlacedPoint;

	//そのターン起きた情報の保存。
	std::vector<std::vector<BoardPoint>> _log;

	//各色の石の総数、黒白の順。
	int _colorCount[2] = { 2,2 };
	
	int _passCount;

	const Vector2Int SEARCH_TABLE[8] = { Vector2Int(0,-1),Vector2Int(1,-1),Vector2Int(1,0),Vector2Int(1,1),Vector2Int(0,1),Vector2Int(-1,1) ,Vector2Int(-1,0),Vector2Int(-1,-1) };

	void reverse(const Vector2Int pos, const BoardStatus color);

public:
	Board();

	void init();
	bool undo();
	bool pass();
	void placedStone(const Vector2Int pos, const BoardStatus color);
	void checkCanPlaced(const Vector2Int pos, const BoardStatus color);
	bool turnEnd();
	void printBoard();
	bool isGameOver();

	std::vector<std::vector<BoardPoint>>& board() { return _board; }
	int passCount() { return _passCount; }
	void resetPassCount();
};