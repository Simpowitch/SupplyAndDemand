#include "City.h"
#include "Hasher.h"

City::City(const Float2 position, const std::string& name, const int population) :
	Entity(position),
	name(name),
	population(population),
	renderData({ {10.0f, 10.0f}, sf::Color::Magenta}),
	growthUpdateTimer(GROWTH_UPDATE_INTERVAL)
{

}

void City::Update(WorldModel* model, const double deltaTime, const double deltaHours)
{
	growthUpdateTimer -= deltaHours;

	if (growthUpdateTimer < 0)
	{
		UpdateGrowth();
		growthUpdateTimer += GROWTH_UPDATE_INTERVAL;
	}
}

uint8_t City::GetInputSlotCount() const
{
	return MAX_INPUTS;
}

InventoryEntry City::GetInputInventory(const size_t index) const
{
	return InventoryEntry{ GOODS_ID[index], inputStorage[index] };
}

void City::CollectRequests(std::vector<TransportRequest>& requests)
{
	for (size_t i = 0; i < MAX_INPUTS; i++)
	{
		int desire = population;
		int threshold = desire * (100 / REQUEST_FOOD_THRESHOLD_PERCENTAGE);
		if (inputStorage[i].current + inputStorage[i].reserved >= threshold)
		{
			return;
		}
		int request = desire - inputStorage[i].current - inputStorage[i].reserved;
		requests.push_back(TransportRequest{ GOODS_ID[i], request, this});
	}
}

int City::PerformDelivery(uint64_t goodsId, int count)
{
	for (std::size_t i = 0; i < MAX_INPUTS && i < inputStorage.size(); ++i)
	{
		if (goodsId != GOODS_ID[i])
		{
			continue;
		}
		inputStorage[i].current += count;
		return count;
	}
	return 0;
}

void City::AddIncomingReservation(uint64_t goodsId, int count)
{
	for (std::size_t i = 0; i < MAX_INPUTS && i < inputStorage.size(); ++i)
	{
		if (goodsId != GOODS_ID[i])
		{
			continue;
		}
		inputStorage[i].reserved += count;
		return;
	}
}

void City::RemoveIncomingReservation(uint64_t goodsId, int count)
{
	for (std::size_t i = 0; i < MAX_INPUTS && i < inputStorage.size(); ++i)
	{
		if (goodsId != GOODS_ID[i])
		{
			continue;
		}
		inputStorage[i].reserved -= count;
		return;
	}
}

void City::UpdateGrowth()
{
	//constexpr uint64_t FOOD_ID = HashString("bread");
	//constexpr float GROWTH_RATE_YEARLY = 1 + (0.0025f / 365); //Simplify to 365 days a year
	//constexpr float STARVATION_RATE_DAILY = 1 - (1.0f / 75); //Starvation sets in between 2-3 months, averaged to 75 days

	//int initialFoodToSupply = population;
	//int foodToSupply = initialFoodToSupply;
	//int availableFood = storage.at(FOOD_ID);
	//foodToSupply -= availableFood;

	//float supplyRate = (foodToSupply - initialFoodToSupply) / initialFoodToSupply;
	//if (supplyRate < 1.0f)
	//{
	//	auto starvationMultiplier = (1.0f - supplyRate) * STARVATION_RATE_DAILY;
	//	population *= starvationMultiplier;
	//}
	//if (supplyRate > 0.0f)
	//{
	//	auto growthMultiplier = GROWTH_RATE_YEARLY * supplyRate;
	//	population *= growthMultiplier;
	//}
}
