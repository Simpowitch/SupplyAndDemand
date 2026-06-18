#include "Factory_Manufacturer.h"
#include "ManufacturerSharedData.h"
#include "Hasher.h"

Factory_Manufacturer::Factory_Manufacturer()
{
	database.Load("resources/manufacturers");
}

Manufacturer Factory_Manufacturer::CreateManufacturer(Float2 position, const std::string& typeName)
{
	auto shared = database.TryGetElement(HashString(typeName));
	if (shared == nullptr)
	{
		//TODO: Print warning
	}
	return Manufacturer(position, shared);
}
