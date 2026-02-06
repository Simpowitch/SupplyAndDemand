#include "World.h"
#include <iostream>

void World::Init(float aWidth, float aHeight, int aManufacturerCount)
{
	manufacturers.reserve(aManufacturerCount);
	for (size_t i = 0; i < aManufacturerCount; i++)
	{
		manufacturers.push_back(Manufacturer{nullptr});
	}
}

void World::Tick()
{
	tickCount++;
	std::cout << "Tick count: " << tickCount << std::endl;
}