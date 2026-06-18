#pragma once
#include <vector>
#include <json.hpp>
#include "Hasher.h"
#include "Goods.h"

struct Recipe
{
	std::vector<GoodsAmount> input;
	std::vector<GoodsAmount> output;

	Recipe(const nlohmann::json& json)
	{
		for (const auto& inputElement : json["inputs"])
		{
			input.push_back({ HashString(inputElement["type"]), inputElement["count"] });
		}

		for (const auto& inputElement : json["outputs"])
		{
			output.push_back({ HashString(inputElement["type"]), inputElement["count"] });
		}
	}
};

