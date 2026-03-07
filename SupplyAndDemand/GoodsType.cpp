#include "GoodsType.h"

const char* TypeToString(GoodsType type)
{
	switch (type)
	{
	case GoodsType::Food:
		return "Food";
	case GoodsType::Electricity:
		return "Electricity";
	case GoodsType::RawMinerals:
		return "Raw Minerals";
	case GoodsType::Coal:
		return "Coal";
	case GoodsType::RefinedGoods:
		return "Refined Goods";
	}
	return "Undefined type name";
}