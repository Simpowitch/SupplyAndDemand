#include "World.h"
#include <iostream>
#include <stdlib.h>
#include "Float2.h"
#include "RNG.h"
#include <string>

World::World(float width, float height) :
	size(width, height)
{

}

void World::Init()
{
	goodsDatabase.Load("resources/goods");

	AddManufacturerOfType("wind_farm");
	AddManufacturerOfType("wheat_farm");
	AddManufacturerOfType("flour_mill");
	AddManufacturerOfType("bakery");
	//AddManufacturerOfType("iron_mine");
	//AddManufacturerOfType("coal_mine");
	//AddManufacturerOfType("steel_factory");
}

void World::AddManufacturerOfType(std::string type)
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

		auto* requesterData = manufacturers[i].GetSharedData();


		for (const auto& inputElement : requesterData->recipe.input)
		{
			auto need = manufacturers[i].GetInputNeed(inputElement.goodsId);
			if (need <= 0)
			{
				continue;
			}

			//There is a need for resources to be delivered
			int bestIndex = -1;
			float bestMagnitude = FLT_MAX;
			for (size_t j = 0; j < manufacturers.size(); j++)
			{
				if (i == j) //Ourself
				{
					continue;
				}

				int available = manufacturers[j].GetAvailableOutput(inputElement.goodsId);
				if (available >= need)
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
				int transportCount = manufacturers[bestIndex].GetAvailableOutput(inputElement.goodsId);
				manufacturers[i].AddDeliveryPledge(inputElement.goodsId, transportCount);
				manufacturers[bestIndex].AddPickupPledge(inputElement.goodsId, transportCount);
				CreateTransportRoute(bestIndex, i, inputElement.goodsId, transportCount);
			}
		}
	}

	//Print state
	system("cls");
	std::cout << "-Manufacturers-" << std::endl;
	for (size_t i = 0; i < manufacturers.size(); i++)
	{
		const auto* data = manufacturers[i].GetSharedData();
		std::cout << data->name << std::endl;
		const auto position = manufacturers[i].GetPosition();
		std::cout << "-Position: " << position.x << " " << position.y << std::endl;
		std::cout << "-Progress:" << manufacturers[i].GetProductionProgress() << std::endl;
		std::cout << "-Storage-" << std::endl;
		const auto& storage = manufacturers[i].GetStorage();
		for(const auto& storageElement : storage)
		{
			auto goods = goodsDatabase.TryGetElement(storageElement.first);
			std::string name = goods == nullptr ? "Unknown" : goods->name;
			std::cout << name << " " << storageElement.second << std::endl;
		}
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
		auto goods = goodsDatabase.TryGetElement(job.goodsId);
		std::string name = goods == nullptr ? "Unknown" : goods->name;
		std::cout << "-Last/Current Job: " << "Delivering " << name << " x" << job.count << " from " << job.pickupId << " to " << job.deliveryId << std::endl;
		goods = goodsDatabase.TryGetElement(transporter.GetGoodsId());
		name = goods == nullptr ? "Unknown" : goods->name;
		std::cout << "-Cargo: " << name << " x" << transporter.GetGoodsCount() << std::endl;
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

	//Remove electricity
	for (auto& manufacturer : manufacturers)
	{
		manufacturer.SetPowerState(false);
		electricityAvailable += manufacturer.GetOutputPower();
		manufacturer.ClearOutputPower();
	}

	//Provide electricity
	for (auto& manufacturer : manufacturers)
	{
		auto powerConsumption = manufacturer.GetSharedData()->powerConsumption;
		if (electricityAvailable >= powerConsumption)
		{
			electricityAvailable -= powerConsumption;
			manufacturer.SetPowerState(true);
		}
	}
}

void World::CreateTransportRoute(int from, int to, uint64_t type, int transportCount)
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
		transporters.push_back(Transporter(Float2{ 0.0f, 0.0f }, 70));
		transportIndex = transporters.size() - 1;
	}

	HaulJob job;
	job.pickupId = from;
	job.pickupPoint = manufacturers[from].GetPosition();
	job.deliveryId = to;
	job.deliveryPoint = manufacturers[to].GetPosition();
	job.count = transportCount;
	job.goodsId = type;

	transporters[transportIndex].SetJob(job);
}