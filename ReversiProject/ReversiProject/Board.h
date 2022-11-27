#pragma once
#include <vector>
#include "Vector2Int.h"
#include "BoardPoint.h"
#include "ColorStorage.h"

class Board
{
	const int BOARD_SIZE = 10;
	const int BOARD_MAX = 64;

	//10*10の盤面、vectorである必要はないが扱いやすいためこれで定義
	std::vector<std::vector<BoardPoint>> _board;

	//そのターン置ける場所
	std::vector<BoardPoint> _canPlacedPoint[61];

	//そのターン起きた情報の保存。
	std::vector<std::vector<BoardPoint>> _log;

	BoardStatus _currentColor = Black;

	//各色の石の総数、黒白の順。
	ColorStorage<int> _colorCount;

	int _passCount;

	const Vector2Int SEARCH_TABLE[8] = { Vector2Int(0,-1),Vector2Int(1,-1),Vector2Int(1,0),Vector2Int(1,1),Vector2Int(0,1),Vector2Int(-1,1) ,Vector2Int(-1,0),Vector2Int(-1,-1) };

	void reverse(const Vector2Int pos, const BoardStatus color);
	void initCanPlacedPoint();

public:
	int turn;
	Board();

	const int BOARD_EVAL[8][8] =
	{
		{100,-50,10,0,0,10,-50,100},
		{-50,-70,-5,-10,-10,-5,-70,-50},
		{10,0,-10,-5,-5,-10,0,10},
		{0,-10,-5,0,0,-5,-10,0},
		{0,-10,-5,0,0,-5,-10,0},
		{10,0,-10,-5,-5,-10,0,10},
		{-50,-70,-5,-10,-10,-5,-70,-50},
		{100,-50,10,0,0,10,-50,100},
	};

	void init();
	bool undo(BoardStatus color);
	bool undo();
	bool pass();
	void placedStone(const Vector2Int pos);
	void checkCanPlaced(const Vector2Int pos, const BoardStatus color);
	bool turnEnd();
	void printBoard();
	bool isGameOver();

	std::vector<std::vector<BoardPoint>>& board() { return _board; }
	std::vector<BoardPoint>& CanPlacedPoint() { return _canPlacedPoint[turn]; }
	int passCount() { return _passCount; }
	int colorCount(BoardStatus color) { return _colorCount[static_cast<int>(color)]; }
	BoardStatus currentColor() { return _currentColor; }
	void resetPassCount();
	void reverseCurrentColor();
};