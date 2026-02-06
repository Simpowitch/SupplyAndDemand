#pragma once
#include <chrono>

class Timer
{
public:
	Timer();
	float Update();

private:
	std::chrono::steady_clock::time_point lastUpdate;
};

