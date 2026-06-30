#pragma once

#include "Entity.h"
#include "HaulJob.h"
#include "Renderer.h"

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
	Transporter(Float2 position, float speed);
	void Update(WorldModel* world, const double deltaTime, const double deltaHours) override;
	bool HasReachedDestination(const Float2& movement) const;
	void MoveTowards(const Float2& movement, const float deltaHours);
	void SetJob(const HaulJob& job);
	
	HaulJob GetJob() const { return currentJob; }
	Status GetCurrentStatus() const { return currentStatus; }
	uint64_t GetGoodsId() const { return cargo.goodsId; }
	int GetGoodsCount() const { return cargo.count; }
	int GetSpeed() const { return mySpeed; }
	RenderInstanceData GetRenderData() const { return renderData; }

private: 
	float mySpeed;
	HaulJob currentJob;
	Status currentStatus = Status::Inactive;
	GoodsAmount cargo;
	RenderInstanceData renderData;
};



