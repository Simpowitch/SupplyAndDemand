#pragma once
#include "Entity.h"
#include "ManufacturerSharedData.h"

class Manufacturer : public Entity
{
public:
	Manufacturer(ManufacturerSharedData* aSharedData);
	void Update(const double deltaTime, const double deltaHours) override;

	ManufacturerSharedData* GetSharedData()
	{
		return sharedData;
	}

	float GetProductionProgress()
	{
		return productionProgress;
	}

	const char* inputName;
	const char* outputName;

	int outputStorage = 0;
	int inputStorage = 0;

private:
	ManufacturerSharedData* sharedData;
	float productionProgress = 0.f;
	
	bool CanProduce();
};

