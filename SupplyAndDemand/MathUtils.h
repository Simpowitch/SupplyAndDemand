#pragma once

#include "Float2.h"
#include "RNG.h"

Float2 GetRandomFloat2(const int xMax, const int yMax)
{
	return Float2(GetRandomInt(0, xMax), GetRandomInt(0, yMax));
}

Float2 GetRandomFloat2(const Float2 max)
{
	return Float2(GetRandomInt(0, max.x), GetRandomInt(0, max.y));
}