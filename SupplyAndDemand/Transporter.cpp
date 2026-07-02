#include "Transporter.h"
#include "WorldModel.h"
#include "GoodsProvider.h"
#include "GoodsRequester.h"

Transporter::Transporter(Float2 position, float speed, int capacity) : 
	Entity(position),
	mySpeed(speed),
	capacity(capacity),
	renderData({{5.0f, 5.0f}, sf::Color::White })
{
	
}

void Transporter::Update(WorldModel* model, const double deltaTime, const double deltaHours)
{
	switch (currentStatus)
	{
	case Status::Inactive:
		break;
	case Status::Pickup:
	{
		Float2 direction = currentJob.provider->GetPickupPosition() - position;
		if (HasReachedDestination(direction))
		{
			//Do pickup
			currentJob.provider->RemoveOutgoingReservation(currentJob.goodsId, currentJob.goodsCount);
			cargo.count += currentJob.provider->PerformPickup(currentJob.goodsId, currentJob.goodsCount);

			currentStatus = Status::Delivery;
		}
		else
		{
			MoveTowards(direction, deltaHours);
		}
		break;
	}
	case Status::Delivery:
	{
		Float2 direction = currentJob.requester->GetDeliveryPosition() - position;
		if (HasReachedDestination(direction))
		{
			//Do delivery
			currentJob.requester->RemoveIncomingReservation(currentJob.goodsId, currentJob.goodsCount);
			cargo.count -= currentJob.requester->PerformDelivery(cargo.goodsId, cargo.count);

			currentStatus = Status::Inactive;
		}
		else
		{
			MoveTowards(direction, deltaHours);
		}
		break;
	}
	default:
		break;
	}
}

bool Transporter::HasReachedDestination(const Float2& distance) const
{
	return distance.SqrMagnitude() < 1.0f;
}

void Transporter::MoveTowards(const Float2& direction, const float deltaHours)
{
	Float2 movement = direction;
	movement.Normalize();
	movement *= mySpeed * deltaHours;
	if (movement.SqrMagnitude() > direction.SqrMagnitude())
	{
		movement = direction;
	}
	position += movement;
}

void Transporter::SetJob(const HaulJob& job)
{
	currentJob = job;
	currentStatus = Status::Pickup;

	if (currentJob.goodsId != cargo.goodsId)
	{
		cargo.goodsId = currentJob.goodsId;
		cargo.count = 0;
	}
}

const char* ToString(const Status& status)
{
	switch (status)
	{
	case Status::Inactive:
		return "Inactive";
	case Status::Pickup:
		return "Pickup";
	case Status::Delivery:
		return "Delivery";
	default:
		return "Undefined string";
	}
}
