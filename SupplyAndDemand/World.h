#pragma once
#include <vector>
#include "Manufacturer.h"
#include "Factory_Manufacturer.h"

class World
{
public:
	void Init(float aWidth, float aHeight, int aManufacturerCount);
	void Update(const float deltaTime);

private:
	static constexpr float SECONDS_TO_HOURS = 1.0f;
	float clock = 0;
	Factory_Manufacturer manufacturerFactory{};
	std::vector<Manufacturer> manufacturers;
};

