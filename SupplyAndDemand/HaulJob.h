#pragma once
#include "Manufacturer.h"
#include "Float2.h"

struct HaulJob
{
	int pickupId = 0;
	Float2 pickupPoint{};
	int deliveryId = 0; 
	Float2 deliveryPoint{};
	int count = 0;
	uint64_t goodsId{};
};