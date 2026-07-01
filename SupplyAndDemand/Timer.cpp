#include "Timer.h"

Timer::Timer(double startTime) :
	time(startTime)
{

}

double Timer::Update(double elapsedTime)
{
	time -= elapsedTime;
	return time;
}
