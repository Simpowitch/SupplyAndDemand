#pragma once
#include "ManufacturerSharedData.h"
#include "Manufacturer.h"
#include "Factory_Type.cpp"
#include <array>

class Factory_Manufacturer
{
public:
	Factory_Manufacturer();
	Manufacturer CreateManufacturer(Float2 position, const Factory_Type type);

private:
	std::array<ManufacturerSharedData, static_cast<int>(Factory_Type::MAX)> sharedData;
};
