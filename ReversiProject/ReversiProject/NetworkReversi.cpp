#include "NetworkReversi.h"
#include "ConsoleManager.h"
#include "PlayerData.h"
#include "NetworkPlayerData.h"

using namespace std;

NetworkReversi::NetworkReversi(NetworkStatus status) :_status(status)
{
	init();
	_board.printBoard();
}

NetworkReversi::~NetworkReversi()
{
	ConsoleManager manager;

	manager.setColor(COL_CYAN);
	cout << endl << "　☆結果発表☆　" << endl;

	manager.setColor(COL_WHITE);
	cout << "黒：" << _board.colorCount(Black) << endl;
	cout << "白：" << _board.colorCount(White) << endl;

	if (_board.colorCount(Black) > _board.colorCount(White))
	{
		cout << "黒の勝ち" << endl;
	}
	else if (_board.colorCount(Black) < _board.colorCount(White))
	{
		cout << "白の勝ち" << endl;
	}
	else
	{
		cout << "引き分け" << endl;
	}

	manager.resetConsoleColor();
}

void NetworkReversi::init()
{
	ConsoleManager consoleManager;

	consoleManager.setConsoleCursorErase();

	if (_status == Host)
	{
		player[0].reset(new PlayerData(Black));
		player[1].reset(new NetworkPlayerData(White));
	}
	else if (_status == Client)
	{
		player[0].reset(new NetworkPlayerData(Black));
		player[1].reset(new PlayerData(White));
	}
}

Vector2Int NetworkReversi::playerTurn(NetworkStatus status)
{
	//はじめにプレイヤーのターンを行う
	if (!player[static_cast<int>(status)]->networkTurn(_board))
	{
		//終了時行う処理があるならここ

		return player[static_cast<int>(status)]->placedPoint;
	}

	return player[static_cast<int>(status)]->placedPoint;
}

void NetworkReversi::enemyTurn(NetworkStatus status, string posData)
{
	Vector2Int pos = Vector2Int(posData[0] - '0', posData[1] - '0');
	int index = status == Host ? 1 : 0;

	player[index]->placedPoint = pos;
	player[index]->networkTurn(_board);
}