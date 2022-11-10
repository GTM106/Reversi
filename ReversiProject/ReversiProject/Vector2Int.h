#pragma once
class Vector2Int
{
public:
	int x;
	int y;

	Vector2Int()
	{
		x = 0;
		y = 0;
	}

	Vector2Int(int x, int y)
	{
		set(x, y);
	}

	void set(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void set_x(int x)
	{
		set(x, y);
	}

	void set_y(int y)
	{
		set(x, y);
	}
};

