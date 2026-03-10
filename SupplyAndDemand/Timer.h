#pragma once
#include <chrono>

class Timer
{
public:
	Timer();
	double Update();

private:
	std::chrono::steady_clock::time_point lastUpdate;
};

