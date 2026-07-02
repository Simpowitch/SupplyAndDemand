#pragma once

#include "Entity.h"
#include "HaulJob.h"
#include "Renderer.h"
#include "Goods.h"

enum class Status
{
	Inactive,
	Pickup,
	Delivery,
};

const char* ToString(const Status& status);


class Transporter : public Entity
{
public:
	Transporter(Float2 position, float speed, int capacity);
	void Update(WorldModel* world, const double deltaTime, const double deltaHours) override;
	bool HasReachedDestination(const Float2& movement) const;
	void MoveTowards(const Float2& movement, const float deltaHours);
	void SetJob(const HaulJob& job);
	
	HaulJob GetJob() const { return currentJob; }
	Status GetCurrentStatus() const { return currentStatus; }
	uint64_t GetGoodsId() const { return cargo.goodsId; }
	int GetGoodsCount() const { return cargo.count; }
	int GetSpeed() const { return mySpeed; }
	int GetCapacity() const { return capacity; }
	RenderInstanceData GetRenderData() const { return renderData; }

	static constexpr int LOW_CAPACITY = 10;
private: 
	float mySpeed;
	int capacity;
	HaulJob currentJob{};
	Status currentStatus = Status::Inactive;
	GoodsAmount cargo{};
	RenderInstanceData renderData;
};



