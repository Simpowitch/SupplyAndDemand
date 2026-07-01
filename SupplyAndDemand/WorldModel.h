#pragma once
#include <vector>
#include "City.h"
#include "Manufacturer.h"
#include "Transporter.h"

struct WorldModel
{
	WorldModel(float width, float height) :
		size(width, height)
	{

	}
	Float2 size;
	double clock = 0;
	int hour = 0;
	std::vector<City> cities;
	std::vector<Manufacturer> manufacturers;
	std::vector<Transporter> transporters;
	int currentPowerBalance = 0;
};

