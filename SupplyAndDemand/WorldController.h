#pragma once
#include "WorldModel.h"
#include "InputManager.h"
#include "Factory_Manufacturer.h"

class WorldController
{
public:
	WorldController(WorldModel* model);
	void ParseInput(const InputManager* inputManager);
	void Update(const double deltaTime);
	void AddManufacturerOfType(std::string type);
private:
	void NewHour();
	void CreateTransportRoute(const int from, const int to, const uint64_t type, const int transportCount);

	WorldModel* model;
	bool isRunning = true;
	Factory_Manufacturer manufacturerFactory;

	static constexpr float SECONDS_TO_HOURS = 1.0f;
};

