#pragma once
#include "BoardPoint.h"
#include "Board.h"
#include "ITurn.h"
#include "INetworkTurn.h"
#include "ConsoleManager.h"

class PlayerData : public ITurn, public INetworkTurn
{
	BoardStatus _color;

	ConsoleManager _consoleManager;	

	void print_board(int h, int v, Board board);
	void input(Board& board);
	void operationExplanation();
	bool isFinishGame(int h, int v, Board board);
public:
	PlayerData(BoardStatus color);

	bool turn(Board& board);

	BoardStatus color() { return _color; }

	// INetworkTurn ‚ğ‰î‚µ‚ÄŒp³‚³‚ê‚Ü‚µ‚½
	virtual bool networkTurn(Board& board) override;
};