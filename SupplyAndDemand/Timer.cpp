#include "Timer.h"

using namespace std::chrono;

Timer::Timer() : lastUpdate(high_resolution_clock::now())
{
	Update();
}

double Timer::Update()
{
	auto current = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(current - lastUpdate);
	lastUpdate = current;
	return duration.count() / 1'000'000.0f; // Convert microseconds to seconds
}
