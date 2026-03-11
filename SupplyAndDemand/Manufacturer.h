#pragma once
#include "Entity.h"
#include "ManufacturerSharedData.h"

class Manufacturer : public Entity
{
public:
	Manufacturer(Float2 position, ManufacturerSharedData* aSharedData);
	void Update(World& world, const double deltaTime, const double deltaHours) override;
	bool CanProduce();

	ManufacturerSharedData* GetSharedData() const
	{
		return sharedData;
	}

	double GetProductionProgress() const
	{
		return productionProgress;
	}

	int GetInputNeed() const
	{
		return sharedData->inputCount - (inputStorage + pledgedDeliveryInput);
	}

	int GetAvailableOutput() const
	{
		return outputStorage - pledgedDeliveryOutput;
	}

	const char* inputName;
	const char* outputName;

	int outputStorage = 0;
	int inputStorage = 0;
	int pledgedDeliveryOutput = 0;
	int pledgedDeliveryInput = 0;


private:
	ManufacturerSharedData* sharedData;
	double productionProgress = 0.;
};

