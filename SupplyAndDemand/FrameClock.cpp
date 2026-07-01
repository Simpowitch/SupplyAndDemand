#include "FrameClock.h"

using namespace std::chrono;


FrameClock::FrameClock() : lastUpdate(high_resolution_clock::now())
{
	Tick();
}

double FrameClock::Tick()
{
	auto current = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(current - lastUpdate);
	lastUpdate = current;
	return duration.count() / 1'000'000.0; // Convert microseconds to seconds
}