#include "Manufacturer.h"
#include "GoodsType.h"

Manufacturer::Manufacturer(ManufacturerSharedData* aSharedData) : 
	sharedData(aSharedData),
	inputName(TypeToString(aSharedData->inputType)),
	outputName(TypeToString(aSharedData->outputType))
{
	
}

void Manufacturer::Update(const double deltaTime, const double deltaHours)
{
	Entity::Update(deltaTime, deltaHours);

	if (CanProduce())
	{
		productionProgress += deltaHours;
		if (productionProgress >= sharedData->productionTime)
		{
			productionProgress -= sharedData->productionTime;
			outputStorage += sharedData->outputCount;
			if (sharedData->inputType != GoodsType::Electricity)
			{
				inputStorage -= sharedData->inputCount;
			}
		}
	}
}

bool Manufacturer::CanProduce()
{
	if (inputStorage < sharedData->inputCount)
	{
		return false;
	}
	return true;
}
