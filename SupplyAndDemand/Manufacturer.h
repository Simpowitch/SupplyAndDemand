#pragma once
#include "Entity.h"
#include "ManufacturerSharedData.h"

class Manufacturer : public Entity
{
public:
	Manufacturer(ManufacturerSharedData* aSharedData);
	void Update(const float deltaTime) override;

private:
	ManufacturerSharedData* sharedData;
	float productionProgress = 0.f;
	int outputStorage = 0;
	int inputStorage = 0;
};

