#pragma once

#include "Entity.h"
#include "HaulJob.h"


class Transporter : public Entity
{
public:
	Transporter(float speed);
	void Update(const double deltaTime, const double deltaHours) override;
	void SetJob(const HaulJob& job);
	
	bool isActive = false;

private: 
	float mySpeed;
	HaulJob currentJob;
};

