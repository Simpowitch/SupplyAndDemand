#pragma once
#include "Entity.h"
#include <string>
#include "Renderer.h"
#include "Timer.h"
#include "GoodsRequester.h"

class City : public Entity, public GoodsRequester
{
public:
	City(const Float2 position, const std::string& name, const int population);
	void Update(WorldModel* model, const double deltaTime, const double deltaHours) override;
	int GetPopulation() const { return population; }
	const std::unordered_map<uint64_t, int> GetStorage() const { return storage; }
	RenderInstanceData GetRenderData() const { return renderData; }

	//GoodsRequester
	void CollectRequests(std::vector<TransportRequest>&) override;
	int PerformDelivery(uint64_t goodsId, int count) override;
	void AddIncomingReservation(uint64_t goodsId, int count) override;
	void RemoveIncomingReservation(uint64_t goodsId, int count) override;
	Float2 GetDeliveryPosition() const override { return Entity::GetPosition(); }
	std::string GetName() const override { return name; }

private:
	void UpdateGrowth();

	std::string name;
	int population;
	std::unordered_map<uint64_t, int> storage;
	int maxStorage = 100;
	double growth = 0.5;
	double growthUpdateTimer;

	static constexpr double GROWTH_UPDATE_INTERVAL = 1.0;

	RenderInstanceData renderData;
};

