#include <iostream>
#include <vector>
#include "PlayerData.h"

using namespace std;

PlayerData::PlayerData(BoardStatus color)
{
	_color = color;
}

void PlayerData::turn(vector<vector<Board>> board)
{
	//TODO：入力読み取り等
	cout << "playerTurn";
}