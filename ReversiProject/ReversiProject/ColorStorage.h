#pragma once
template<typename T > class ColorStorage
{
	T data[3];
public:
	T& operator[](int color)
	{
		return data[color + 1];
	}
	const T& operator[](int color) const
	{
		return data[static_cast<int>(color + 1)];
	}
};