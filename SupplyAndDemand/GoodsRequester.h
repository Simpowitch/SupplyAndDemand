#pragma once
#include <vector>
#include "TransportRequest.h"
#include "Float2.h"
#include <string>

class GoodsRequester
{
public:
	virtual ~GoodsRequester() = default;
	virtual void CollectRequests(std::vector<TransportRequest>&) = 0;
	virtual int PerformDelivery(uint64_t goodsId, int count) = 0;
	virtual void AddIncomingReservation(uint64_t goodsId, int count) = 0;
	virtual void RemoveIncomingReservation(uint64_t goodsId, int count) = 0;
	virtual Float2 GetDeliveryPosition() const = 0;
	virtual std::string GetName() const = 0;
};
