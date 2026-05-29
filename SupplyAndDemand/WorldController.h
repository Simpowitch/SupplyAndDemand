#pragma once
#include "WorldModel.h"
#include "InputManager.h"
#include "Factory_Manufacturer.h"

class WorldController
{
public:
	WorldController(WorldModel* model, InputManager* inputManager);
	void ParseInput();
	void Update(const double deltaTime);
	void AddManufacturerOfType(std::string type);
private:
	void NewHour();
	void CreateTransportRoute(const int from, const int to, const uint64_t type, const int transportCount);

	WorldModel* model;
	InputManager* inputManager;
	bool isRunning = true;
	Factory_Manufacturer manufacturerFactory;

	static constexpr float SECONDS_TO_HOURS = 1.0f;
};

