#include "Transporter.h"

Transporter::Transporter(float speed) : 
	mySpeed(speed)
{

}

void Transporter::Update(const double deltaTime, const double deltaHours)
{
	Entity::Update(deltaTime, deltaHours);
	//TODO: Travel to the first point first, then the second

	if (isActive)
	{

		Point movement = currentJob.toPoint - position;

		if (movement.SqrMagnitude() > 1.0f)
		{
			movement.Normalize();
			movement *= mySpeed;
			position += movement;
		}
		else
		{
			isActive = false;

			//TODO: Deliver goods
		}
	}
}

void Transporter::SetJob(const HaulJob& job)
{
	currentJob = job;
	isActive = true;
	//TODO: Pickup goods

}
