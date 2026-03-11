#pragma once
#include "Point.h"

class Entity
{
public:
	virtual void Update(const double deltaTime, const double deltaHours);
	Point GetPosition() const
	{
		return position;
	}
protected:
	Point position;
};

