#pragma once
#include <vector>
#include "Manufacturer.h"
#include "Factory_Manufacturer.h"
#include "Transporter.h"

class World
{
public:
	void Init(float width, float height, int manufacturerCount);
	void AddManufacturerOfType(Factory_Type type);
	void Update(const double deltaTime);
	Manufacturer GetManufacturer(int index);

private:
	static constexpr float SECONDS_TO_HOURS = 1.0f;
	double clock = 0;
	int hour = 0;
	Factory_Manufacturer manufacturerFactory{};
	std::vector<Manufacturer> manufacturers;
	std::vector<Transporter> transporters;

	void NewHour();
	void CreateTransportRoute(int from, int to, GoodsType type, int transportCount);
};

