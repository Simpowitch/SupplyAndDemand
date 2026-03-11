#pragma once

#include <random>

std::random_device seed;
std::mt19937 rng(seed());

int GetRandomInt(int min, int max)
{
	std::uniform_int_distribution<int> rndDist(min, max);
	return rndDist(rng);
}

