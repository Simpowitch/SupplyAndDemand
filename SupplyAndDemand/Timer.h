#pragma once

class Timer
{
public:
	Timer(double startTime);
	double Update(double elapsedTime);

private:
	double time;
};

