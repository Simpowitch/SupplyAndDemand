#pragma once
#include "Entity.h"
#include "ManufacturerSharedData.h"

class Manufacturer : public Entity
{
public:
	Manufacturer(ManufacturerSharedData* aSharedData);

private:
	ManufacturerSharedData* sharedData;
};

