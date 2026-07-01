#pragma once
#include <cstdint>

class GoodsRequester;

struct TransportRequest
{
	uint64_t goodsId;
	int requestCount;
	GoodsRequester* requester;
};