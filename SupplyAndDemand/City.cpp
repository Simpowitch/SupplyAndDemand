#include "City.h"
#include "Hasher.h"
#include "math.h"

City::City(const Float2 position, const std::string& name, const int population) :
	Entity(position),
	name(name),
	population(population),
	renderData({ {10.0f, 10.0f}, sf::Color::Magenta}),
	growthUpdateTimer(GROWTH_UPDATE_INTERVAL)
{
	for (size_t i = 0; i < MAX_INPUTS; i++)
	{
		inputStorage[i].current = population * INITIAL_DAYS_WITH_SUPPLIES;
	}
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
		int desire = population * DESIRED_DAYS_WITH_SUPPLIES;
		int threshold = desire * (100 / REQUEST_GOODS_THRESHOLD_PERCENTAGE);
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
	constexpr int DAILY_UPDATES = 24;
	constexpr float GROWTH_RATE = 1 + (0.0025f / 365 / DAILY_UPDATES); //365 days per year, 24 hours a day update
	constexpr float LEAVE_RATE = 1 - (1.0f / 365 / DAILY_UPDATES); //365 days per year, 24 hours a day update

	int contentScore = 0;

	for (size_t i = 0; i < MAX_INPUTS; i++)
	{
		int desire = population;
		int availability = inputStorage[i].current;
		int highThreshold = desire * (100 / REQUEST_GOODS_THRESHOLD_PERCENTAGE);
		int lowThreshold = desire * (100 / CRITICA_GOODS_THRESHOLD_PERCENTAGE);

		if (availability >= highThreshold)
		{
			contentScore++;
		}
		else if (availability < lowThreshold)
		{
			contentScore--;
		}

		inputStorage[i].current -= desire / DAILY_UPDATES;
		if (inputStorage[i].current < 0)
		{
			inputStorage[i].current = 0;
		}
	}

	if (contentScore > 0)
	{
		auto growthMultiplier = std::pow(GROWTH_RATE, contentScore);
		population *= growthMultiplier;
	}
	if (contentScore < 0)
	{
		auto starvationMultiplier = std::pow(LEAVE_RATE, -contentScore);
		population *= starvationMultiplier;
	}
}
