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
	//パスに成功したら弾く（置く場所がなかった）
	if (board.pass())
	{
		if (!board.turnEnd())return false;
		return true;
	}

	try
	{
		input(board);
	}
	catch(ForcedTerminationException)//強制終了選択肢を感知したら終了させる
	{
		cout << "……ゲームを終了します。" << endl;
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

	//現在の地点を特殊表示
	print_board(h, v, board);

	bool isPrintOperationExplanation = false;

	//入力
	int val = 0;
	while (val != KEY_ENTER)
	{
		switch ((val = _getch()))
		{
			//上
		case KEY_8:
		case KEY_W:
		case KEY_UP:
			if (v == 1)	continue;
			v--;

			break;
			//下
		case KEY_2:
		case KEY_S:
		case KEY_DOWN:
			if (v == static_cast<int>(board.board().size() - 2))continue;
			v++;

			break;
			//左
		case KEY_4:
		case KEY_A:
		case KEY_LEFT:
			if (h == 1)continue;
			h--;

			break;
			//右
		case KEY_6:
		case KEY_D:
		case KEY_RIGHT:
			if (h == static_cast<int>(board.board().size() - 2))continue;
			h++;

			break;
			//決定
		case KEY_ENTER:
			if (board.board()[v][h].direction() == 0)
			{
				val = 0;
				_consoleManager.setColor(COL_RED);
				cout << "そこには置けません。" << endl;
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
				cout << "それ以上戻せません" << endl;
				_consoleManager.resetConsoleColor();
				continue;
			}

			//2回行って自分のターンに戻る
			board.undo(_color);

			//パスの盤面が進行不能になるからそれ以前まで戻す
			while (board.CanPlacedPoint().empty())
			{
				if (!board.undo(_color))break;
				
				//2回行って自分のターンに戻る
				board.undo(_color);
			}

			break;

		case KEY_TAB:
			isPrintOperationExplanation ^= true;
			break;
		case KEY_ESC:
			if (isFinishGame(h, v, board))throw ForcedTerminationException();//安全に強制終了させる
			break;
		default:
			continue;
		}

		//現在の地点を特殊表示
		print_board(h, v, board);
		if (isPrintOperationExplanation)operationExplanation();
	}
}

void PlayerData::operationExplanation()
{
	_consoleManager.setColor(COL_CYAN);
	cout << "　☆ 操作説明 ☆　" << endl;
	cout << "[移動] 　　  WASD・テンキー・矢印キー" << endl;
	cout << "[やり直し]　 U" << endl;
	cout << "[石を打つ]　 ENTER" << endl;
	cout << "[閉じる]　　 TAB" << endl;
	cout << "[ゲーム終了] ESC" << endl;
	_consoleManager.resetConsoleColor();
}

bool PlayerData::isFinishGame(int h, int v, Board board)
{
	bool isFinish = false;

	print_board(h, v, board);
	_consoleManager.setColor(COL_YELLOW);
	cout << "ゲームを終了しますか？" << endl;
	if (isFinish)cout << "→";
	cout << "　　はい" << endl;
	if (!isFinish)cout << "→";
	cout << "　　いいえ" << endl;

	_consoleManager.resetConsoleColor();

	int val = 0;
	while (val != KEY_ENTER)
	{
		switch ((val = _getch()))
		{
			//上
		case KEY_8:
		case KEY_W:
		case KEY_UP:
			if (isFinish)continue;
			isFinish = true;
			break;
			//下
		case KEY_2:
		case KEY_S:
		case KEY_DOWN:
			if (!isFinish)continue;
			isFinish = false;
			break;
			//決定
		case KEY_ENTER:
			return isFinish;
		case KEY_ESC:
			return false;
		default:
			continue;
		}

		print_board(h, v, board);
		_consoleManager.setColor(COL_YELLOW);
		cout << "ゲームを終了しますか？" << endl;
		if (isFinish)cout << "→";
		cout << "　　はい" << endl;
		if (!isFinish)cout << "→";
		cout << "　　いいえ" << endl;
		_consoleManager.resetConsoleColor();
	}

	return false;
}

//通常とは異なる特殊な盤面表示
void PlayerData::print_board(int h, int v, Board _board)
{
	//コンソールのクリア
	_consoleManager.console_clear();

	//操作説明表示のヘルプ
	_consoleManager.setColor(COL_CYAN);
	cout << endl << endl << "TABキーを押して操作説明を表示…" << endl;
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
				if (_board.board()[i][j].direction() != 0) cout << "・";
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

			if (h == j && v == i)_consoleManager.resetConsoleColor();

			cout << "|";
		}
		cout << endl;
		cout << "-------------------------------" << endl;
	}
}