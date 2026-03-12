#include "World.h"
#include <iostream>
#include <stdlib.h>
#include "Float2.h"
#include "RNG.h"

World::World(float width, float height) :
	size(width, height)
{

}

void World::Init()
{
	AddManufacturerOfType(Factory_Type::Electricity_Wind);
	AddManufacturerOfType(Factory_Type::Mine_Minerals);
	AddManufacturerOfType(Factory_Type::Goods);
}

void World::AddManufacturerOfType(Factory_Type type)
{
	manufacturers.push_back(manufacturerFactory.CreateManufacturer(Float2(GetRandomInt(0, size.x), GetRandomInt(0, size.y)), type));
}

void World::Update(const double deltaTime)
{
	double deltaHours = deltaTime / SECONDS_TO_HOURS;
	clock += deltaHours;

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


	for (size_t i = 0; i < manufacturers.size(); i++)
	{
		manufacturers[i].Update(*this, deltaTime, deltaHours);
	}

	for (size_t i = 0; i < transporters.size(); i++)
	{
		transporters[i].Update(*this, deltaTime, deltaHours);
	}

	//Check if transports are needed
	for (size_t i = 0; i < manufacturers.size(); i++)
	{
		if (manufacturers[i].CanProduce())
		{
			continue;
		}

		auto *requesterData = manufacturers[i].GetSharedData();
		//There is a need for resources to be delivered
		int need = manufacturers[i].GetInputNeed();
		if (requesterData->inputType != GoodsType::Electricity && need > 0)
		{
			int bestIndex = -1;
			float bestMagnitude = FLT_MAX;
			for (size_t j = 0; j < manufacturers.size(); j++)
			{
				if (i == j)
				{
					continue;
				}
				auto* providerData = manufacturers[j].GetSharedData();
				if (providerData->outputType != requesterData->inputType)
				{
					continue;
				}
				int available = manufacturers[j].GetAvailableOutput();
				if (available > need)
				{
					auto sqrMagnitude = (manufacturers[i].GetPosition() - manufacturers[j].GetPosition()).SqrMagnitude();

					if (sqrMagnitude < bestMagnitude)
					{
						bestIndex = j;
						bestMagnitude = sqrMagnitude;
					}
				}
			}

			if (bestIndex != -1)
			{
				//Make pledge
				int transportCount = manufacturers[bestIndex].GetAvailableOutput();
				manufacturers[i].pledgedDeliveryInput += transportCount;
				manufacturers[bestIndex].pledgedDeliveryOutput += transportCount;
				CreateTransportRoute(bestIndex, i, requesterData->inputType, transportCount);
			}
		}
	}



	//Print state
	system("cls");
	std::cout << "-Manufacturers-" << std::endl;
	for (size_t i = 0; i < manufacturers.size(); i++)
	{
		auto* data = manufacturers[i].GetSharedData();
		std::cout << "Manufacturer (" << i << ")" << std::endl;
		auto position = manufacturers[i].GetPosition();
		std::cout << "-Position: " << position.x << " " << position.y << std::endl;
		std::cout << "-Progress:" << manufacturers[i].GetProductionProgress() << std::endl;
		std::cout << "-Input storage:" << manufacturers[i].inputName << " " << manufacturers[i].inputStorage << std::endl;
		std::cout << "-Output storage:" << manufacturers[i].outputName << " " << manufacturers[i].outputStorage << std::endl;
		std::cout << "-------------------" << std::endl;
	}

	std::cout << "-Transporters-" << std::endl;
	for (size_t i = 0; i < transporters.size(); i++)
	{
		const Transporter& transporter = transporters[i];
		std::cout << "Transporter (" << i << ")" << std::endl;
		auto position = transporter.GetPosition();
		std::cout << "-Position: " << position.x << " " << position.y << std::endl;
		std::cout << "-State: " << ToString(transporter.GetCurrentStatus()) << std::endl;
		const HaulJob job = transporter.GetJob();
		std::cout << "-Last/Current Job: " << "Delivering " << ToString(job.type) << " x" << job.count << " from " << job.pickupId << " to " << job.deliveryId << std::endl;
		std::cout << "-Cargo: " << ToString(transporter.GetGoodsType()) << " x" << transporter.GetGoodsCount() << std::endl;
		std::cout << "-Speed: " << transporter.GetSpeed() << std::endl;
		std::cout << "-------------------" << std::endl;
	}

	
	std::cout << "-Time-" << std::endl;
	std::cout << "Clock: " << clock << std::endl;
	std::cout << "Hour: " << hour << std::endl;
}

Manufacturer& World::GetManufacturer(int index)
{
	return manufacturers[index];
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

void World::CreateTransportRoute(int from, int to, GoodsType type, int transportCount)
{
	int transportIndex = -1;

	for (size_t i = 0; i < transporters.size(); i++)
	{
		if (transporters[i].GetCurrentStatus() != Status::Inactive)
		{
			continue;
		}
		transportIndex = 0;
	}

	if (transportIndex == -1)
	{
		transporters.push_back(Transporter(Float2{0.0f, 0.0f}, 70));
		transportIndex = transporters.size() - 1;
	}
	
	HaulJob job;
	job.pickupId = from;
	job.pickupPoint = manufacturers[from].GetPosition();
	job.deliveryId = to;
	job.deliveryPoint = manufacturers[to].GetPosition();
	job.count = transportCount;
	job.type = type;
	
	transporters[transportIndex].SetJob(job);
}