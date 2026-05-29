#include "WorldController.h"
#include "RNG.h"
#include <iostream>

WorldController::WorldController(WorldModel* model, InputManager* inputManager) :
	model(model), inputManager(inputManager)
{
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
	model->manufacturers.push_back(manufacturerFactory.CreateManufacturer(Float2(GetRandomInt(0, model->size.x), GetRandomInt(0, model->size.y)), type));
}

void WorldController::ParseInput()
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
}

void WorldController::Update(const double deltaTime)
{
	if (!isRunning)
	{
		return;
	}
	double deltaHours = deltaTime / SECONDS_TO_HOURS;
	model->clock += deltaHours;

	if (model->clock - model->hour >= 1.0)
	{
		model->hour++;
		NewHour();
		if (model->hour >= 24)
		{
			model->hour = 0;
		}
	}
	if (model->clock >= 24)
	{
		model->clock -= 24;
	}

	for (auto& manufacturer : model->manufacturers)
	{
		manufacturer.Update(model, deltaTime, deltaHours);
	}

	for (auto& transporter : model->transporters)
	{
		transporter.Update(model, deltaTime, deltaHours);
	}

	//TODO: Can this 3rd loop be inserted into the 1st above?

	//Check if transports are needed
	for (size_t i = 0; i < model->manufacturers.size(); i++)
	{
		if (model->manufacturers[i].CanProduce())
		{
			continue;
		}

		auto* requesterData = model->manufacturers[i].GetSharedData();


		for (const auto& inputElement : requesterData->recipe.input)
		{
			auto need = model->manufacturers[i].GetInputNeed(inputElement.goodsId);
			if (need <= 0)
			{
				continue;
			}

			//There is a need for resources to be delivered
			int bestIndex = -1;
			float bestMagnitude = FLT_MAX;
			for (size_t j = 0; j < model->manufacturers.size(); j++)
			{
				if (i == j) //Ourself
				{
					continue;
				}

				int available = model->manufacturers[j].GetAvailableOutput(inputElement.goodsId);
				if (available >= need)
				{
					auto sqrMagnitude = (model->manufacturers[i].GetPosition() - model->manufacturers[j].GetPosition()).SqrMagnitude();

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
				int transportCount = model->manufacturers[bestIndex].GetAvailableOutput(inputElement.goodsId);
				model->manufacturers[i].AddDeliveryPledge(inputElement.goodsId, transportCount);
				model->manufacturers[bestIndex].AddPickupPledge(inputElement.goodsId, transportCount);
				CreateTransportRoute(bestIndex, i, inputElement.goodsId, transportCount);
			}
		}
	}
}

void WorldController::NewHour()
{
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
}

void WorldController::CreateTransportRoute(const int from, const int to, const uint64_t type, const int transportCount)
{
	int transportIndex = -1;

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
	job.pickupId = from;
	job.pickupPoint = model->manufacturers[from].GetPosition();
	job.deliveryId = to;
	job.deliveryPoint = model->manufacturers[to].GetPosition();
	job.count = transportCount;
	job.goodsId = type;

	model->transporters[transportIndex].SetJob(job);
}
