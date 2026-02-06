#include "World.h"
#include <iostream>
#include <stdlib.h>

void World::Init(float aWidth, float aHeight, int aManufacturerCount)
{
	manufacturers.reserve(aManufacturerCount);
	for (size_t i = 0; i < aManufacturerCount; i++)
	{
		manufacturers.emplace_back(manufacturerFactory.CreateManufacturer(Factory_Type::Mine_Minerals));
	}
}

void World::Update(const float deltaTime)
{
	system("cls");


	for (size_t i = 0; i < manufacturers.size(); i++)
	{
		manufacturers[i].Update(deltaTime);
	}

	clock += deltaTime / SECONDS_TO_HOURS;
	if (clock >= 24)
	{
		clock -= 24;
	}

	//Print state
	std::cout << "Clock: " << clock;
}