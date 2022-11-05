#pragma once

enum BoardStatus
{
	None,
	White,
	Black,
	Wall,

	Max
};

class Board
{
	BoardStatus _status;
	bool _can_placed;

public:
	Board(BoardStatus status);

	void reverse();

	BoardStatus status() { return _status; }
	bool can_placed() { return _can_placed; }

	void set_status(BoardStatus status);
	void set_can_placed(bool enable);
};

