#include "Manufacturer.h"
#include "Goods.h"

Manufacturer::Manufacturer(Float2 position, const ManufacturerSharedData* aSharedData) : 
	Entity(position),
	sharedData(aSharedData),
	isPowered(sharedData->powerConsumption <= 0),
	renderData({ {20.0, 10.0f}, sf::Color(sharedData->mapColor) })
{

}

void Manufacturer::Update(WorldModel* model, const double deltaTime, const double deltaHours)
{
	if (CanProduce())
	{
		productionProgress += deltaHours;
		if (productionProgress >= sharedData->productionTime)
		{
			productionProgress -= sharedData->productionTime;

			for (const auto& recipeElement : sharedData->recipe.output)
			{
				storage[recipeElement.goodsId] += recipeElement.count;
			}

			outputPower += sharedData->powerProduction;

			for (const auto& recipeElement : sharedData->recipe.input)
			{
				storage[recipeElement.goodsId] -= recipeElement.count;
			}
		}
	}
}

bool Manufacturer::CanProduce()
{
	if (!isPowered)
	{
		return false;
	}
	for (const auto& recipeElement : sharedData->recipe.input)
	{
		if (storage[recipeElement.goodsId] < recipeElement.count)
		{
			return false;
		}
	}
	return true;
}

int Manufacturer::GetInputNeed(uint64_t goodsType) const
{
	for (const auto& recipeElement : sharedData->recipe.input)
	{
		if (recipeElement.goodsId != goodsType)
		{
			continue;
		}
		int inStorage = 0;
		int pledged = 0;

		auto it = storage.find(goodsType);
		if (it != storage.end())
		{
			inStorage = it->second;
		}

		it = deliveryPledge.find(goodsType);
		if (it != deliveryPledge.end())
		{
			pledged = it->second;
		}

		return recipeElement.count - (inStorage + pledged);
	}
	return 0;
}

int Manufacturer::GetAvailableOutput(uint64_t goodsType) const
{
	//If we need the goods, never allow anyone to take it
	for (const auto& recipeElement : sharedData->recipe.input)
	{
		if (recipeElement.goodsId == goodsType)
		{
			return 0;
		}
	}

	int inStorage = 0;
	int pledged = 0;

	auto it = storage.find(goodsType);
	if (it != storage.end())
	{
		inStorage = it->second;
	}

	it = deliveryPledge.find(goodsType);
	if (it != deliveryPledge.end())
	{
		pledged = it->second;
	}

	return inStorage - pledged;
}

int Manufacturer::PerformPickup(uint64_t type, int count)
{
	//Clamp to what exists in storage if exceeding
	int inStorage = storage[type];
	if (inStorage < count)
	{
		count = inStorage;
	}

	storage[type] -= count;
	return count;
}

int Manufacturer::PerformDelivery(uint64_t type, int count)
{
	storage[type] += count;
	return count;
}

void Manufacturer::AddDeliveryPledge(uint64_t type, int count)
{
	deliveryPledge[type] += count;
}

void Manufacturer::AddPickupPledge(uint64_t type, int count)
{
	pickupPledge[type] += count;
}

void Manufacturer::RemoveDeliveryPledge(uint64_t type, int count)
{
	deliveryPledge[type] -= count;
}

void Manufacturer::RemovePickupPledge(uint64_t type, int count)
{
	pickupPledge[type] -= count;
}

void Manufacturer::SetPowerState(bool newState)
{
	isPowered = newState;
}
