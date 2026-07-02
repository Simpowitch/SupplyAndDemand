#pragma once
#include "Entity.h"
#include <string>
#include "Renderer.h"
#include "Timer.h"
#include "GoodsRequester.h"
#include "Goods.h"

class City : public Entity, public GoodsRequester
{
public:
	City(const Float2 position, const std::string& name, const int population);
	void Update(WorldModel* model, const double deltaTime, const double deltaHours) override;
	int GetPopulation() const { return population; }
	uint8_t GetInputSlotCount() const;
	InventoryEntry GetInputInventory(const size_t index) const;
	RenderInstanceData GetRenderData() const { return renderData; }

	//GoodsRequester
	void CollectRequests(std::vector<TransportRequest>& requests) override;
	int PerformDelivery(uint64_t goodsId, int count) override;
	void AddIncomingReservation(uint64_t goodsId, int count) override;
	void RemoveIncomingReservation(uint64_t goodsId, int count) override;
	Float2 GetDeliveryPosition() const override { return Entity::GetPosition(); }
	std::string GetName() const override { return name; }

private:
	void UpdateGrowth();

	static constexpr double GROWTH_UPDATE_INTERVAL = 1.0;
	static constexpr int REQUEST_GOODS_THRESHOLD_PERCENTAGE = 80;
	static constexpr int CRITICA_GOODS_THRESHOLD_PERCENTAGE = 20;
	static constexpr uint8_t MAX_INPUTS = 2;
	static constexpr std::array<uint64_t, MAX_INPUTS> GOODS_ID = { HashString("bread"), HashString("steel") };

	std::string name;
	int population;
	std::array<GoodsState, MAX_INPUTS> inputStorage;
	double growth = 0.5;
	double growthUpdateTimer;
	RenderInstanceData renderData;
};

