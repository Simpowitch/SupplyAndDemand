#pragma once

#include <math.h>

struct Point
{
	float x;
	float y;

	Point() :
		x(0),
		y(0)
	{

	}
	Point(float x, float y) :
		x(x),
		y(y)
	{

	}

	Point operator+(const Point& p)
	{
		return Point(x + p.x, y + p.y);
	}

	Point operator+=(const Point& p)
	{
		x += p.x;
		y += p.y;
		return *this;
	}

	Point operator-(const Point& p)
	{
		return Point(x - p.x, y - p.y);
	}

	Point operator-=(const Point& p)
	{
		x -= p.x;
		y -= p.y;
		return *this;
	}

	Point operator*(float m)
	{
		return Point(x * m, y * m);
	}

	Point operator*=(float m)
	{
		x *= m;
		y *= m;
		return *this;
	}
	
	float SqrMagnitude()
	{
		return x * x + y * y;
	}

	void Normalize()
	{
		if (x == 0 && y == 0)
		{
			return;
		}
		auto magnitude = sqrtf(SqrMagnitude());
		x /= magnitude;
		y /= magnitude;
	}
};

