#include "Manufacturer.h"
#include <iostream>

Manufacturer::Manufacturer(ManufacturerSharedData* aSharedData)
{
	sharedData = aSharedData;
}

void Manufacturer::Update(const float deltaTime)
{
	productionProgress += deltaTime;

	if (productionProgress >= sharedData->productionTime)
	{
		productionProgress -= sharedData->productionTime;
		outputStorage += sharedData->outputCount;
		inputStorage -= sharedData->inputCount;

		std::cout << "Produced " << sharedData->outputCount << " of " << static_cast<int>(sharedData->outputType)
			<< ", total output storage: " << outputStorage << "\n";
	}
}
