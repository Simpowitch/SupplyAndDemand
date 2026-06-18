#pragma once
#include "Recipe.h"
#include <json.hpp>
#include <string>
#include "Hasher.h"

struct ManufacturerSharedData
{
	ManufacturerSharedData(const nlohmann::json& json)
		: id(HashString(json["id"])), name(json["name"]), mapColor(ToColor(json["mapColor"])), recipe(json["recipe"]), productionTime(json["production_time"]), powerConsumption(json["power_consumption"]), powerProduction(json["power_production"])
	{

	}

	static uint32_t ToColor(const nlohmann::json& json)
	{
		return (static_cast<uint32_t>(json["r"]) << 24) |
			(static_cast<uint32_t>(json["g"]) << 16) |
			(static_cast<uint32_t>(json["b"]) << 8) |
			static_cast<uint32_t>(json["a"]);
	}

	uint64_t id;
	std::string name;
	uint32_t mapColor;
	Recipe recipe;
	float productionTime;
	int powerConsumption;
	int powerProduction;
};

