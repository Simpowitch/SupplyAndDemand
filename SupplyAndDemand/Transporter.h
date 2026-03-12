#pragma once

#include "Entity.h"
#include "HaulJob.h"

enum class Status
{
	Inactive,
	Pickup,
	Delivery,
};

const char* ToString(Status status);


class Transporter : public Entity
{
public:
	Transporter(Float2 position, float speed);
	void Update(World& world, const double deltaTime, const double deltaHours) override;
	bool HasReachedDestination(const Float2& movement) const;
	void MoveTowards(const Float2& movement, const float deltaHours);
	void SetJob(const HaulJob& job);
	
	HaulJob GetJob() const { return currentJob; }
	Status GetCurrentStatus() const { return currentStatus; }
	GoodsType GetGoodsType() const { return goodsType; }
	int GetGoodsCount() const { return goodsCount; }
	int GetSpeed() const { return mySpeed; }

private: 
	float mySpeed;
	HaulJob currentJob;
	Status currentStatus;
	int goodsCount;
	GoodsType goodsType;
};



