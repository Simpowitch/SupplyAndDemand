#pragma once
class Entity
{
public:
	virtual void Update(const float deltaTime, const float deltaHours);

private:
	float xPos = 0.0f;
	float yPos = 0.0f;
};

