#pragma once
#include "Entity.h"
#include "ManufacturerSharedData.h"
#include <unordered_map>
#include "Renderer.h"
#include "GoodsRequester.h"
#include "GoodsProvider.h"
#include <array>

struct GoodsState
{
	int current{};
	int reserved{};

	int GetUnreserved() const { return current - reserved; }
};

struct InventoryEntry
{
	uint64_t goodsId{};
	GoodsState goods{};
};

class Manufacturer : public Entity, public GoodsRequester, public GoodsProvider
{
public:
	Manufacturer(Float2 position, const ManufacturerSharedData* aSharedData);
	void Update(WorldModel* model, const double deltaTime, const double deltaHours) override;
	bool CanProduce();

	const ManufacturerSharedData* GetSharedData() const
	{
		return sharedData;
	}

	double GetProductionProgress() const
	{
		return productionProgress;
	}

	int GetOutputPower() const { return outputPower; }
	void ClearOutputPower()
	{
		outputPower = 0;
	}
	void SetPowerState(bool newState);
	bool GetPowerState() const { return isPowered; }
	RenderInstanceData GetRenderData() const { return renderData; }

	uint8_t GetInputSlotCount() const;
	InventoryEntry GetInputInventory(const size_t index) const;
	uint8_t GetOutputSlotCount() const;
	InventoryEntry GetOutputInventory(const size_t index) const;

	std::string GetName() const override { return sharedData->name; }

	//GoodsRequester
	void CollectRequests(std::vector<TransportRequest>&) override;
	int PerformDelivery(uint64_t goodsId, int count) override;
	void AddIncomingReservation(uint64_t goodsId, int count) override;
	void RemoveIncomingReservation(uint64_t goodsId, int count) override;
	Float2 GetDeliveryPosition() const override { return Entity::GetPosition() + Float2(-5, 0); } 

	//GoodsProvider
	int GetAvailableSupply(const uint64_t goodsId) const override;
	int PerformPickup(uint64_t goodsId, int count) override;
	void AddOutgoingReservation(uint64_t goodsId, int count) override;
	void RemoveOutgoingReservation(uint64_t goodsId, int count) override;
	Float2 GetPickupPosition() const override { return Entity::GetPosition() + Float2(5, 0); } 

private:
	const ManufacturerSharedData* sharedData;
	double productionProgress = 0.;
	bool isPowered = false;
	int outputPower = 0;
	RenderInstanceData renderData;

	static constexpr uint8_t MAX_INPUTS = 4;
	static constexpr uint8_t MAX_OUTPUTS = 4;
	static constexpr int DESIRED_INPUT_COUNT = 100;
	static constexpr int REQUEST_INPUT_THRESHOLD = 80;

	std::array<GoodsState, MAX_INPUTS> inputStorage;
	std::array<GoodsState, MAX_OUTPUTS> outputStorage;
};

