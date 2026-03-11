#pragma once
#include "Manufacturer.h"
#include "GoodsType.h"
#include "Point.h"

struct HaulJob
{
	int fromId = 0;
	Point fromPoint{};
	int toId = 0; 
	Point toPoint{};
	int count = 0;
	GoodsType type{};
};