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

			for (std::size_t i = 0; i < MAX_INPUTS && i < sharedData->recipe.input.size(); ++i)
			{
				inputStorage[i].current -= sharedData->recipe.input[i].count;
			}

			for (std::size_t i = 0; i < MAX_OUTPUTS && i < sharedData->recipe.output.size(); ++i)
			{
				outputStorage[i].current += sharedData->recipe.output[i].count;
			}

			outputPower += sharedData->powerProduction;
		}
	}
}

bool Manufacturer::CanProduce()
{
	if (!isPowered)
	{
		return false;
	}
	for (std::size_t i = 0; i < MAX_INPUTS && i < sharedData->recipe.input.size(); ++i)
	{
		if (inputStorage[i].current < sharedData->recipe.input[i].count)
		{
			return false;
		}
	}
	return true;
}

void Manufacturer::SetPowerState(bool newState)
{
	isPowered = newState;
}

uint8_t Manufacturer::GetInputSlotCount() const
{
	return sharedData->recipe.input.size();
}

InventoryEntry Manufacturer::GetInputInventory(const size_t index) const
{
	return InventoryEntry{ sharedData->recipe.input[index].goodsId, inputStorage[index] };
}

uint8_t Manufacturer::GetOutputSlotCount() const
{
	return sharedData->recipe.output.size();
}

InventoryEntry Manufacturer::GetOutputInventory(const size_t index) const
{
	return InventoryEntry{ sharedData->recipe.output[index].goodsId, outputStorage[index] };
}

//Goods requester
void Manufacturer::CollectRequests(std::vector<TransportRequest>& requests)
{
	for (std::size_t i = 0; i < MAX_INPUTS && i < sharedData->recipe.input.size(); ++i)
	{
		const auto& slot = inputStorage[i];
		if (slot.current + slot.reserved >= REQUEST_INPUT_THRESHOLD)
		{
			continue;
		}
		const int amount = DESIRED_INPUT_COUNT - slot.current - slot.reserved;
		if (amount > 0)
		{
			requests.push_back(TransportRequest{ sharedData->recipe.input[i].goodsId, amount, this});
		}
	}
}

int Manufacturer::PerformDelivery(const uint64_t goodsId, int count)
{
	for (std::size_t i = 0; i < MAX_INPUTS && i < sharedData->recipe.input.size(); ++i)
	{
		if (goodsId != sharedData->recipe.input[i].goodsId)
		{
			continue;
		}
		inputStorage[i].current += count;
		return count;
	}
	return 0;
}

void Manufacturer::AddIncomingReservation(const uint64_t goodsId, const int count)
{
	for (std::size_t i = 0; i < MAX_INPUTS && i < sharedData->recipe.input.size(); ++i)
	{
		if (goodsId != sharedData->recipe.input[i].goodsId)
		{
			continue;
		}
		inputStorage[i].reserved += count;
		return;
	}
}

void Manufacturer::RemoveIncomingReservation(const uint64_t goodsId, const int count)
{
	for (std::size_t i = 0; i < MAX_INPUTS && i < sharedData->recipe.input.size(); ++i)
	{
		if (goodsId != sharedData->recipe.input[i].goodsId)
		{
			continue;
		}
		inputStorage[i].reserved -= count;
		return;
	}
}


//Goods provider
int Manufacturer::GetAvailableSupply(const uint64_t goodsId) const
{
	for (std::size_t i = 0; i < MAX_OUTPUTS && i < sharedData->recipe.output.size(); ++i)
	{
		if (goodsId != sharedData->recipe.output[i].goodsId)
		{
			continue;
		}
		return outputStorage[i].GetUnreserved();
	}
	return 0;
}

int Manufacturer::PerformPickup(const uint64_t goodsId, int count)
{
	for (std::size_t i = 0; i < MAX_OUTPUTS && i < sharedData->recipe.output.size(); ++i)
	{
		if (goodsId != sharedData->recipe.output[i].goodsId)
		{
			continue;
		}
		auto& slot = outputStorage[i];
		int inStorage = slot.GetUnreserved();

		//Clamp to what exists in storage if exceeding
		if (inStorage < count)
		{
			count = inStorage;
		}
		slot.current -= count;
		return count;
	}
	return 0;
}

void Manufacturer::AddOutgoingReservation(const uint64_t goodsId, const int count)
{
	for (std::size_t i = 0; i < MAX_OUTPUTS && i < sharedData->recipe.output.size(); ++i)
	{
		if (goodsId != sharedData->recipe.output[i].goodsId)
		{
			continue;
		}
		outputStorage[i].reserved += count;
		return;
	}
}

void Manufacturer::RemoveOutgoingReservation(const uint64_t goodsId, const int count)
{
	for (std::size_t i = 0; i < MAX_OUTPUTS && i < sharedData->recipe.output.size(); ++i)
	{
		if (goodsId != sharedData->recipe.output[i].goodsId)
		{
			continue;
		}
		outputStorage[i].reserved -= count;
		return;
	}
}
