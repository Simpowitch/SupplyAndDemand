#pragma once
#include "GoodsRequester.h"
#include "GoodsProvider.h"

struct HaulJob
{
	GoodsRequester* requester;
	GoodsProvider* provider;
	uint64_t goodsId;
	int goodsCount;
};