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
				if (_board[i][j].direction() != 0) cout << "・";
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

void Board::placedStone(const Vector2Int pos, const BoardStatus color)
{
	_board[pos.x][pos.y].setStatus(color);
	reverse(pos, color);
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

			//その結果を記録
			updateLog.push_back(_board[x][y]);

			//次回の場所に遷移
			x += SEARCH_TABLE[i].x;
			y += SEARCH_TABLE[i].y;
		}

	}

	_log.push_back(updateLog);
}

void Board::checkCanPlaced(const Vector2Int pos, const BoardStatus color)
{
	//すでに置かれていたら弾く
	if (_board[pos.x][pos.y].status() != BoardStatus::None)return;

	unsigned direction = 0;
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
		}

		//最後が自分の色ならビットを立てる
		if (_board[x][y].status() == color)direction |= (1 << i);
	}

	//置ける場所があるなら置ける場所の地点に登録
	if (direction != 0)	_canPlacedPoint.push_back(_board[pos.x][pos.y]);

	_board[pos.x][pos.y].setDirection(direction);
}

bool Board::undo()
{
	if (_log.size() <= 1)return false;

	auto undoMethod = [this]()
	{
		int index = static_cast<int>(_log.size() - 1);

		Vector2Int pos = _log[index][0].position();
		_board[pos.x][pos.y].setStatus(None);

		for (int i = 1; i < _log[index].size(); i++)
		{
			pos = _log[index][i].position();
			_board[pos.x][pos.y].reverse();
		}

		//今回もとに戻したログを削除
		_log.pop_back();

	};

	//2回同じ処理を呼び出すことで直前の自分のターンに戻る
	undoMethod();
	undoMethod();

	return true;
}

bool Board::pass()
{
	if (_canPlacedPoint.size() > 0)return false;

	//空の配列を代入
	_log.push_back(vector<BoardPoint>());
	return true;
}

void Board::turnEnd()
{
	_canPlacedPoint.clear();
}