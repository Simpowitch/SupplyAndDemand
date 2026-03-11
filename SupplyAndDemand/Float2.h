#pragma once

#include <math.h>

struct Float2
{
	float x;
	float y;

	Float2() :
		x(0),
		y(0)
	{

	}
	Float2(float x, float y) :
		x(x),
		y(y)
	{

	}

	Float2 operator+(const Float2& p) const
	{
		return Float2(x + p.x, y + p.y);
	}

	Float2 operator+=(const Float2& p)
	{
		x += p.x;
		y += p.y;
		return *this;
	}

	Float2 operator-(const Float2& p) const
	{
		return Float2(x - p.x, y - p.y);
	}

	Float2 operator-=(const Float2& p)
	{
		x -= p.x;
		y -= p.y;
		return *this;
	}

	Float2 operator*(float m) const
	{
		return Float2(x * m, y * m);
	}

	Float2 operator*=(float m)
	{
		x *= m;
		y *= m;
		return *this;
	}
	
	float SqrMagnitude() const
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

