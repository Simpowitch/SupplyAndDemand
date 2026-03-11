#pragma once

#include "Entity.h"
#include "HaulJob.h"

enum class Status
{
	Inactive,
	Pickup,
	Delivery
};

class Transporter : public Entity
{
public:
	Transporter(Float2 position, float speed);
	void Update(World& world, const double deltaTime, const double deltaHours) override;
	bool HasReachedDestination(const Float2& movement) const;
	void MoveTowards(const Float2& movement, const float deltaHours);
	void SetJob(const HaulJob& job);
	
	Status GetCurrentStatus()
	{
		return currentStatus;
	}

private: 
	float mySpeed;
	HaulJob currentJob;
	Status currentStatus;
	int goodsCount;
	GoodsType goodsType;
};



