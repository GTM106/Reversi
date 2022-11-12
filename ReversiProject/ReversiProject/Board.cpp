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
		//’¼Ú\’z‚ÅV‚½‚È—v‘f‚ğ––”ö‚É’Ç‰Á‚·‚é
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
				if (_board[i][j].direction() != 0) cout << "E";
				else cout << "@";
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

void Board::placedStone(const Vector2Int pos, const BoardStatus color)
{
	_board[pos.x][pos.y].setStatus(color);
	reverse(pos, color);
}

void Board::reverse(const Vector2Int pos, const BoardStatus color)
{
	vector<BoardPoint> updateLog;
	int x, y;

	//’u‚¢‚½’n“_‚ğ‚Ü‚¸‹L˜^
	updateLog.push_back(_board[pos.x][pos.y]);

	//”ª•ûŒüAƒrƒbƒg‚ª—§‚Á‚Ä‚é’n“_‚É’Tõ‚µA”½“]ˆ—
	for (int i = 0; i < 8; i++)
	{
		if (!(_board[pos.x][pos.y].direction() & 1 << i))continue;

		x = pos.x + SEARCH_TABLE[i].x;
		y = pos.y + SEARCH_TABLE[i].y;

		while (_board[x][y].status() != color)
		{
			//Î‚ğ”½“]‚³‚¹‚Ä
			_board[x][y].reverse();

			//‚»‚ÌŒ‹‰Ê‚ğ‹L˜^
			updateLog.push_back(_board[x][y]);

			//Ÿ‰ñ‚ÌêŠ‚É‘JˆÚ
			x += SEARCH_TABLE[i].x;
			y += SEARCH_TABLE[i].y;
		}

	}

	_log.push_back(updateLog);
}

void Board::checkCanPlaced(const Vector2Int pos, const BoardStatus color)
{
	//‚·‚Å‚É’u‚©‚ê‚Ä‚¢‚½‚ç’e‚­
	if (_board[pos.x][pos.y].status() != BoardStatus::None)return;

	unsigned direction = 0;
	int x, y;

	for (int i = 0; i < 8; i++)
	{
		x = pos.x + SEARCH_TABLE[i].x;
		y = pos.y + SEARCH_TABLE[i].y;

		//’u‚¢‚½F‚Ì”½“]‚µ‚½FˆÈŠO‚È‚ç’e‚¢‚ÄŸ‚Ìtable
		if (_board[x][y].status() != -color)continue;

		//’u‚¢‚½F‚Ì”½“]‚µ‚½F‚ª‘±‚­‚Ü‚Å‘±s
		while (_board[x][y].status() == -color)
		{
			x += SEARCH_TABLE[i].x;
			y += SEARCH_TABLE[i].y;
		}

		//ÅŒã‚ª©•ª‚ÌF‚È‚çƒrƒbƒg‚ğ—§‚Ä‚é
		if (_board[x][y].status() == color)direction |= (1 << i);
	}

	//ï¿½uï¿½ï¿½ï¿½ï¿½êŠï¿½ï¿½ï¿½ï¿½ï¿½ï¿½È‚ï¿½uï¿½ï¿½ï¿½ï¿½êŠï¿½Ì’nï¿½_ï¿½É“oï¿½^
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

		//¡‰ñ‚à‚Æ‚É–ß‚µ‚½ƒƒO‚ğíœ
		_log.pop_back();

	};

	//2‰ñ“¯‚¶ˆ—‚ğŒÄ‚Ño‚·‚±‚Æ‚Å’¼‘O‚Ì©•ª‚Ìƒ^[ƒ“‚É–ß‚é
	undoMethod();
	undoMethod();

	return true;
}

bool Board::pass()
{
	if (_canPlacedPoint.size() > 0)return false;

	//ï¿½ï¿½Ì”zï¿½ï¿½ï¿½ï¿½ï¿½
	_log.push_back(vector<BoardPoint>());
	return true;
}

void Board::turnEnd()
{
	_canPlacedPoint.clear();
}