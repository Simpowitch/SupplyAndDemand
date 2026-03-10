#pragma once
class Entity
{
public:
	virtual void Update(const double deltaTime, const double deltaHours);

private:
	float xPos = 0.0f;
	float yPos = 0.0f;
};

