#pragma once
#include "Board.h"

class EntityData
{
	BoardStatus _color;

public:
	EntityData(BoardStatus color) { _color = color; }
	BoardStatus color() { return _color; }
};

