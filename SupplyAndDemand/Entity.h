#pragma once
class Entity
{
public:
	virtual void Update(const float deltaTime);

private:
	float xPos = 0.0f;
	float yPos = 0.0f;
};

