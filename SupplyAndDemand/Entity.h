#pragma once
#include "Float2.h"

struct WorldModel;

class Entity
{
public:
	Entity(Float2 position);
	virtual void Update(WorldModel* model, const double deltaTime, const double deltaHours) = 0;
	Float2 GetPosition() const
	{
		return position;
	}
protected:
	Float2 position;
};

