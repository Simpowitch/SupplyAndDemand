#pragma once
#include "WorldModel.h"
#include "InputManager.h"
#include "Factory_Manufacturer.h"
#include <array>

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

	int simulationSpeedIndex = 3;
	static constexpr int SIMULATION_SPEED_STEPS = 7;
	std::array<float, SIMULATION_SPEED_STEPS> simlationSpeeds = { 0.125f, 0.25f, 0.5f, 1.0f, 2.0f, 4.0f, 8.0f };

	static constexpr float SECONDS_TO_HOURS = 1.0f;
};

