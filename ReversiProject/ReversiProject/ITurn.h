#pragma once
#include "Board.h"

//プレイヤー、コンピュータのターン処理の実装を強制するインターフェースのようなもの
class ITurn
{
public:
	virtual	bool turn(Board& board) = 0;
};