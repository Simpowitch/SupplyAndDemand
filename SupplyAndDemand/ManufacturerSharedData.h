#pragma once
#include "GoodsType.h"

struct ManufacturerSharedData
{
	float productionTime;
	GoodsType inputType; //Unused if input is 0
	int inputCount;
	GoodsType outputType;
	int outputCount;
};

