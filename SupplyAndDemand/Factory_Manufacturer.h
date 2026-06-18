#pragma once
#include "ManufacturerSharedData.h"
#include "Manufacturer.h"
#include <array>
#include "Database.h"
#include <string>

class Factory_Manufacturer
{
public:
	Factory_Manufacturer();
	Manufacturer CreateManufacturer(Float2 position, const std::string& typeName);

private:
	Database<ManufacturerSharedData> database;
};
