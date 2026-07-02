#pragma once

#include "Float2.h"
#include "RNG.h"
#include <math.h>
#include <vector>


Float2 GetRandomFloat2(const int xMax, const int yMax)
{
	return Float2(GetRandomInt(0, xMax), GetRandomInt(0, yMax));
}

Float2 GetRandomFloat2(const Float2 max)
{
	return Float2(GetRandomInt(0, max.x), GetRandomInt(0, max.y));
}

int GetClosest(const Float2 origin, const std::vector<Float2>& targets)
{
	float bestMagnitude = FLT_MAX;
	int bestIndex = -1;

	for (size_t i = 0; i < targets.size(); i++)
	{
		auto sqrMagnitude = (origin - targets[i]).SqrMagnitude();

		if (sqrMagnitude >= bestMagnitude)
		{
			continue;
		}
		bestIndex = i;
		bestMagnitude = sqrMagnitude;
	}
	return bestIndex;
}