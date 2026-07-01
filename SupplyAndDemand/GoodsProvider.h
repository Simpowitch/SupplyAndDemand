#pragma once
#include "Float2.h"
#include <string>

class GoodsProvider 
{
public:
	virtual ~GoodsProvider() = default;
	virtual int GetAvailableSupply(const uint64_t goodsId) const = 0;
	virtual int PerformPickup(uint64_t goodsId, int count) = 0;
	virtual void AddOutgoingReservation(uint64_t goodsId, int count) = 0;
	virtual void RemoveOutgoingReservation(uint64_t goodsId, int count) = 0;
	virtual Float2 GetPickupPosition() const = 0;
	virtual std::string GetName() const = 0;
};
