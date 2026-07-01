#include "WorldController.h"
#include "RNG.h"
#include <iostream>
#include <math.h>
#include "MathUtils.h"
#include "TransportRequest.h"

WorldController::WorldController(WorldModel* model) :
	model(model)
{
	model->cities.push_back(City(GetRandomFloat2(model->size), "Stockholm", 100));
	model->cities.push_back(City(GetRandomFloat2(model->size), "Malmö", 50));
	model->cities.push_back(City(GetRandomFloat2(model->size), "Göteborg", 50));

	AddManufacturerOfType("wind_farm");
	AddManufacturerOfType("wheat_farm");
	AddManufacturerOfType("flour_mill");
	AddManufacturerOfType("bakery");
	AddManufacturerOfType("iron_mine");
	AddManufacturerOfType("coal_mine");
	AddManufacturerOfType("steel_factory");
}


void WorldController::AddManufacturerOfType(std::string type)
{
	model->manufacturers.push_back(manufacturerFactory.CreateManufacturer(GetRandomFloat2(model->size), type));
}

void WorldController::ParseInput(const InputManager* inputManager)
{
	if (inputManager->WasKeyPressed('P'))
	{
		if (isRunning)
		{
			isRunning = false;
			std::cout << "Paused\n";
		}
		else
		{
			isRunning = true;
			std::cout << "Unpaused\n";
		}
	}
	if (inputManager->WasKeyPressed('A'))
	{
		simulationSpeedIndex = std::min(simulationSpeedIndex + 1, SIMULATION_SPEED_STEPS - 1);
	}
	else if (inputManager->WasKeyPressed('B'))
	{
		simulationSpeedIndex = std::max(simulationSpeedIndex - 1, 0);
	}
}

void WorldController::Update(const double deltaTime)
{
	if (!isRunning)
	{
		return;
	}
	double simulatedDeltaTime = simlationSpeeds[simulationSpeedIndex] * deltaTime;
	double deltaHours = simulatedDeltaTime / SECONDS_TO_HOURS;
	model->clock += deltaHours;

	if (model->clock - model->hour >= 1.0)
	{
		model->hour++;
		NewHour();
		if (model->hour >= 24)
		{
			model->hour = 0;
			//NewDay();
		}
	}
	if (model->clock >= 24)
	{
		model->clock -= 24;
	}

	for (auto& city : model->cities)
	{
		city.Update(model, simulatedDeltaTime, deltaHours);
	}

	for (auto& manufacturer : model->manufacturers)
	{
		manufacturer.Update(model, simulatedDeltaTime, deltaHours);
	}

	for (auto& transporter : model->transporters)
	{
		transporter.Update(model, simulatedDeltaTime, deltaHours);
	}
}

void WorldController::NewHour()
{
	//Electricity update
	model->currentPowerBalance = 0;
	int electricityAvailable = 0;

	//Collect electricity
	for (auto& manufacturer : model->manufacturers)
	{
		electricityAvailable += manufacturer.GetOutputPower();
		manufacturer.ClearOutputPower();
	}

	//Provide electricity
	for (auto& manufacturer : model->manufacturers)
	{
		auto powerConsumption = manufacturer.GetSharedData()->powerConsumption;
		if (electricityAvailable >= powerConsumption)
		{
			electricityAvailable -= powerConsumption;
			manufacturer.SetPowerState(true);
		}
		else
		{
			model->currentPowerBalance -= powerConsumption;
			manufacturer.SetPowerState(false);
		}
	}

	model->currentPowerBalance += electricityAvailable;

	//Check request needs
	std::vector<TransportRequest> requests;
	for (auto& city : model->cities)
	{
		city.CollectRequests(requests);
	}
	for (auto& manufacturer : model->manufacturers)
	{
		manufacturer.CollectRequests(requests);
	}
	//Find providers
	for (auto& request : requests)
	{
		int bestIndex = -1;
		float bestMagnitude = FLT_MAX;
		for (size_t i = 0; i < model->manufacturers.size(); i++)
		{
			int available = model->manufacturers[i].GetAvailableSupply(request.goodsId);
			if (available <= 0)
			{
				continue;
			}

			if (available < request.requestCount) //For now we must fullfill the whole demand in one go
			{
				continue;
			}

			auto sqrMagnitude = (request.requester->GetDeliveryPosition() - model->manufacturers[i].GetPickupPosition()).SqrMagnitude();
			if (sqrMagnitude >= bestMagnitude)
			{
				continue;
			}
			bestIndex = i;
			bestMagnitude = sqrMagnitude;
		}

		if (bestIndex != -1)
		{
			GoodsProvider& provider = model->manufacturers[bestIndex];
			int transportCount = std::min(provider.GetAvailableSupply(request.goodsId), request.requestCount);
			CreateTransportRoute(&provider, request.requester, request.goodsId, transportCount);
		}
	}
}

void WorldController::CreateTransportRoute(GoodsProvider* provider, GoodsRequester* requester, const uint64_t type, const int transportCount)
{
	int transportIndex = -1;

	//Reuse any idle transporters
	//TODO: Improvement, get the closest one
	for (size_t i = 0; i < model->transporters.size(); i++)
	{
		if (model->transporters[i].GetCurrentStatus() != Status::Inactive)
		{
			continue;
		}
		transportIndex = i;
		break;
	}

	if (transportIndex == -1)
	{
		model->transporters.push_back(Transporter(Float2{ 0.0f, 0.0f }, 70));
		transportIndex = model->transporters.size() - 1;
	}

	HaulJob job;
	job.requester = requester;
	job.provider = provider;
	job.goodsId = type;
	job.goodsCount = transportCount;

	model->transporters[transportIndex].SetJob(job);

	provider->AddOutgoingReservation(type, transportCount);
	requester->AddIncomingReservation(type, transportCount);
}
