#include "Manufacturer.h"
#include "GoodsType.h"

Manufacturer::Manufacturer(Float2 position, ManufacturerSharedData* aSharedData) : 
	Entity(position),
	sharedData(aSharedData),
	inputName(ToString(aSharedData->inputType)),
	outputName(ToString(aSharedData->outputType))
{
	
}

void Manufacturer::Update(World& world, const double deltaTime, const double deltaHours)
{
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
