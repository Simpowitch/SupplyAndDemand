#pragma once
#include <nlohmann/json.hpp>
#include "Hasher.h"

struct Goods
{
	const int id;
	const std::string name;
	const uint64_t value;

	Goods(const nlohmann::json& json)
		: id(HashString(json["id"])), name(json["name"]), value(json["value"])
	{

	}
};

struct GoodsAmount
{
	uint64_t goodsId;
	int count;
};