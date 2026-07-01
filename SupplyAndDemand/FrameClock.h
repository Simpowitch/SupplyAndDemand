#pragma once
#include <chrono>

class FrameClock
{
public:
	FrameClock();
	double Tick();

private:
	std::chrono::steady_clock::time_point lastUpdate;
};

