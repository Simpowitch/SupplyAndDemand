#pragma once
#include <vector>
#include "Manufacturer.h"

class World
{
public:
	void Init(float aWidth, float aHeight, int aManufacturerCount);
	void Tick();

private:
	unsigned int tickCount = 0;
	std::vector<Manufacturer> manufacturers;
};

