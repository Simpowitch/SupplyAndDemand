#include "Factory_Manufacturer.h"
#include "ManufacturerSharedData.h"
#include "GoodsType.h"

Factory_Manufacturer::Factory_Manufacturer()
{
	int max = static_cast<int>(Factory_Type::MAX);
	for (size_t i = 0; i < max; i++)
	{
		auto type = static_cast<Factory_Type>(i);
		ManufacturerSharedData data;

		//TODO: Read from json instead
		switch (type)
		{
			case Factory_Type::Mine_Minerals:
			{
				data.productionTime = 1.0f;
				data.inputCount = 1;
				data.inputType = GoodsType::Electricity;
				data.outputCount = 1;
				data.outputType = GoodsType::RawMinerals;
				break;
			}
			case Factory_Type::Mine_Coal:
			{
				data.productionTime = 1.0f;
				data.inputCount = 1;
				data.inputType = GoodsType::Electricity;
				data.outputCount = 1;
				data.outputType = GoodsType::Coal;
				break;
			}
			case Factory_Type::Goods:
			{
				data.productionTime = 24.0f;
				data.inputCount = 5;
				data.inputType = GoodsType::RawMinerals;
				data.outputCount = 1;
				data.outputType = GoodsType::RefinedGoods;
				break;
			}
			case Factory_Type::Electricity_Wind:
			{
				data.productionTime = 1.0f;
				data.inputCount = 0;
				data.inputType = GoodsType::Electricity; //Nothing actually needed
				data.outputCount = 6;
				data.outputType = GoodsType::Electricity;
				break;
			}
			case Factory_Type::Electricity_Coal:
			{
				data.productionTime = 1.0f;
				data.inputCount = 250;
				data.inputType = GoodsType::Coal;
				data.outputCount = 500;
				data.outputType = GoodsType::Electricity;
				break;
			}
		}
		sharedData[i] = data;
	}
}

Manufacturer Factory_Manufacturer::CreateManufacturer(const Factory_Type type)
{
	return Manufacturer(&sharedData[static_cast<int>(type)]);
}
