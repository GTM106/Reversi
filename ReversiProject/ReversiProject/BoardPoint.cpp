#include "BoardPoint.h"

BoardPoint::BoardPoint(BoardStatus status, Vector2Int pos) :_status(status), _canPlace(false), _position(pos), _direction(0), _reverseCount(0)
{
}

void BoardPoint::setCanPlaced(bool enable)
{
	_canPlace = enable;
}

void BoardPoint::setStatus(BoardStatus status)
{
	_status = status;
}

void BoardPoint::reverse()
{
	_status = static_cast<BoardStatus>(-_status);
}

void BoardPoint::setDirection(unsigned dir)
{
	_direction = dir;
}

void BoardPoint::addReverseCount(unsigned count)
{
	_reverseCount += count;
}

void BoardPoint::resetReverseCount()
{
	_reverseCount = 0;
}
