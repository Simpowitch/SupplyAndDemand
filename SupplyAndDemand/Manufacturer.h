#pragma once
#include "Entity.h"
#include "ManufacturerSharedData.h"
#include <unordered_map>

class Manufacturer : public Entity
{
public:
	Manufacturer(Float2 position, const ManufacturerSharedData* aSharedData);
	void Update(World& world, const double deltaTime, const double deltaHours) override;
	bool CanProduce();

	const ManufacturerSharedData* GetSharedData() const
	{
		return sharedData;
	}

	const std::unordered_map<uint64_t, int> GetStorage() const
	{
		return storage;
	}

	double GetProductionProgress() const
	{
		return productionProgress;
	}

	int GetInputNeed(uint64_t goodsType) const;
	int GetAvailableOutput(uint64_t goodsType) const;
	int PerformPickup(uint64_t type, int count);
	int PerformDelivery(uint64_t type, int count);
	void AddDeliveryPledge(uint64_t type, int count);
	void AddPickupPledge(uint64_t type, int count);
	void RemoveDeliveryPledge(uint64_t type, int count);
	void RemovePickupPledge(uint64_t type, int count);
	int GetOutputPower() const { return outputPower; }
	void ClearOutputPower()
	{
		outputPower = 0;
	}
	void SetPowerState(bool newState);
	bool GetPowerState() const { return isPowered; }

private:
	const ManufacturerSharedData* sharedData;
	double productionProgress = 0.;
	bool isPowered = false;
	int outputPower = 0;
	std::unordered_map<uint64_t, int> storage;
	std::unordered_map<uint64_t, int> deliveryPledge;
	std::unordered_map<uint64_t, int> pickupPledge;
};

