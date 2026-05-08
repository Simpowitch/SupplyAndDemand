#pragma once
#include "Recipe.h"
#include <nlohmann/json.hpp>
#include <string>
#include "Hasher.h"

struct ManufacturerSharedData
{
	ManufacturerSharedData(const nlohmann::json& json)
		: id(HashString(json["id"])), name(json["name"]), recipe(json["recipe"]), productionTime(json["production_time"]), powerConsumption(json["power_consumption"]), powerProduction(json["power_production"])
	{

	}

	uint64_t id;
	std::string name;
	Recipe recipe;
	float productionTime;
	int powerConsumption;
	int powerProduction;
};

