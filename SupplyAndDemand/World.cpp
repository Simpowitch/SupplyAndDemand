#include "World.h"
#include <iostream>
#include <stdlib.h>

void World::Init(float aWidth, float aHeight, int aManufacturerCount)
{
	manufacturers.reserve(aManufacturerCount);
	/*for (size_t i = 0; i < aManufacturerCount; i++)
	{
		manufacturers.emplace_back(manufacturerFactory.CreateManufacturer(Factory_Type::Mine_Minerals));
	}*/

	manufacturers.emplace_back(manufacturerFactory.CreateManufacturer(Factory_Type::Electricity_Wind));
	manufacturers.emplace_back(manufacturerFactory.CreateManufacturer(Factory_Type::Mine_Minerals));
	manufacturers.emplace_back(manufacturerFactory.CreateManufacturer(Factory_Type::Goods));
}

void World::Update(const double deltaTime)
{
	system("cls");

	double deltaHours = deltaTime / SECONDS_TO_HOURS;
	clock += deltaHours;

	for (size_t i = 0; i < manufacturers.size(); i++)
	{
		manufacturers[i].Update(deltaTime, deltaHours);
	}

	//Print state
	for (size_t i = 0; i < manufacturers.size(); i++)
	{
		auto* data = manufacturers[i].GetSharedData();
		std::cout << "Manufacturer (" << i << ")" << std::endl;
		std::cout << "-Progress:" << manufacturers[i].GetProductionProgress() << std::endl;
		std::cout << "-Input storage:" << manufacturers[i].inputName << " " << manufacturers[i].inputStorage << std::endl;
		std::cout << "-Output storage:" << manufacturers[i].outputName << " " << manufacturers[i].outputStorage << std::endl;
		std::cout << "-------------------" << std::endl;
	}

	

	if (clock - hour >= 1.0)
	{
		hour++;
		NewHour();
		if (hour >= 24)
		{
			hour = 0;
		}
	}
	if (clock >= 24)
	{
		clock -= 24;
	}

	std::cout << "-------------------" << std::endl;
	std::cout << "Clock: " << clock << std::endl;
	std::cout << "Hour: " << hour << std::endl;
}

void World::NewHour()
{
	int electricityAvailable = 0;
	for (auto& manufacturer : manufacturers)
	{
		auto *data = manufacturer.GetSharedData();
		//Clear old electricity from manufacturers input storages
		if (data->inputType == GoodsType::Electricity && data->inputCount > 0)
		{
			manufacturer.inputStorage = 0;
		}
		//Collect electricity
		if (data->outputType == GoodsType::Electricity && manufacturer.outputStorage > 0)
		{
			electricityAvailable += manufacturer.outputStorage;
			manufacturer.outputStorage = 0;
		}
	}

	//Provide electricity
	if (electricityAvailable > 0)
	{
		for (auto& manufacturer : manufacturers)
		{
			auto* data = manufacturer.GetSharedData();

			if (data->inputType == GoodsType::Electricity && data->inputCount > 0)
			{
				auto demand = data->inputCount;
				if (electricityAvailable >= demand)
				{
					manufacturer.inputStorage += demand;
					electricityAvailable -= demand;
					if (electricityAvailable <= 0)
					{
						break;
					}
				}
			}
		}
	}
}