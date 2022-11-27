#include <iostream>
#include "Board.h"

using namespace std;

Board::Board() :_passCount(0), turn(0)
{
	//初期石数
	_colorCount[static_cast<int>(Black)] = 2;
	_colorCount[static_cast<int>(None)] = 60;
	_colorCount[static_cast<int>(White)] = 2;

	//盤面の初期化
	init();
}

void Board::init()
{
	_board.clear();
	_log.clear();

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		//直接構築で新たな要素を末尾に追加する
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
				if (CanPlacedPoint()[turn].direction() != 0) cout << "・";
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

	//置いた地点をまず記録
	updateLog.push_back(_board[pos.x][pos.y]);

	//八方向、ビットが立ってる地点に探索し、反転処理
	for (int i = 0; i < 8; i++)
	{
		if (!(_board[pos.x][pos.y].direction() & 1 << i))continue;

		x = pos.x + SEARCH_TABLE[i].x;
		y = pos.y + SEARCH_TABLE[i].y;

		while (_board[x][y].status() != color)
		{
			//石を反転させて
			_board[x][y].reverse();

			//石の総数を保存
			_colorCount[static_cast<int>(color)]++;
			_colorCount[static_cast<int>(-color)]--;

			//その結果を記録
			updateLog.push_back(_board[x][y]);

			//次回の場所に遷移
			x += SEARCH_TABLE[i].x;
			y += SEARCH_TABLE[i].y;
		}
	}

	//今回のログを保存
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
	//すでに置かれていたら弾く
	if (_board[pos.x][pos.y].status() != BoardStatus::None)
	{
		_board[pos.x][pos.y].setDirection(0);
		_board[pos.x][pos.y].resetReverseCount();
		return;
	}

	//反転できる個数をリセット
	_board[pos.x][pos.y].resetReverseCount();

	unsigned direction = 0;
	unsigned reverseCount = 0;
	int x, y;

	for (int i = 0; i < 8; i++)
	{
		x = pos.x + SEARCH_TABLE[i].x;
		y = pos.y + SEARCH_TABLE[i].y;

		//置いた色の反転した色以外なら弾いて次のtable
		if (_board[x][y].status() != -color)continue;

		//置いた色の反転した色が続くまで続行
		while (_board[x][y].status() == -color)
		{
			x += SEARCH_TABLE[i].x;
			y += SEARCH_TABLE[i].y;
			reverseCount++;
		}

		//最後が自分の色ならビットを立てる
		if (_board[x][y].status() == color)
		{
			direction |= (1 << i);
			_board[pos.x][pos.y].addReverseCount(reverseCount);
		}
		else reverseCount = 0;
	}

	_board[pos.x][pos.y].setDirection(direction);

	//置ける場所があるなら置ける場所の地点に登録
	//if (direction != 0)	_canPlacedPoint[turn].push_back(_board[pos.x][pos.y]);
}

bool Board::undo(BoardStatus color)
{
	//白のときと黒のときで戻せる限界値が違う
	int limit = color == Black ? 0 : 1;
	if (_log.size() <= limit)return false;

	//一手戻すため、現在の色を反転させる
	_currentColor = static_cast<BoardStatus>(-_currentColor);

	//最新の情報は後ろにある
	vector<BoardPoint>& latestInfo = _log.back();

	//情報がなかったらパスしたターン
	if (latestInfo.empty())
	{
		//今回もとに戻したログを削除
		_log.pop_back();

		return true;
	}

	//打った地点のundo
	Vector2Int pos = latestInfo[0].position();
	_board[pos.x][pos.y].setStatus(None);

	//石の総数を保存
	_colorCount[static_cast<int>(latestInfo[0].status())]--;
	_colorCount[static_cast<int>(None)]++;

	//reverseした地点のundo
	for (int i = 1; i < latestInfo.size(); i++)
	{
		pos = latestInfo[i].position();
		_board[pos.x][pos.y].reverse();

		//石の総数を保存
		_colorCount[static_cast<int>(latestInfo[i].status())]--;
		_colorCount[static_cast<int>(-latestInfo[i].status())]++;
	}

	//今回もとに戻したログを削除
	_log.pop_back();

	//ターンを戻す
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

	//空の配列を代入
	_log.push_back(vector<BoardPoint>());

	//パス回数を記録。連続2回でゲーム終了
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