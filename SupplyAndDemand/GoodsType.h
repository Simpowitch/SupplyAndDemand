#pragma once

enum class GoodsType
{
	Food,
	Electricity,
	RawMinerals,
	Coal,
	RefinedGoods,
};

const char* TypeToString(GoodsType type);
