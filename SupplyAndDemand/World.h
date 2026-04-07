#pragma once
#include <vector>
#include "Manufacturer.h"
#include "Factory_Manufacturer.h"
#include "Transporter.h"
#include "Database.h"
#include "Goods.h"
#include "Recipe.h"

class World
{
public:
	World(float width, float height);
	void Init();
	void AddManufacturerOfType(Factory_Type type);
	void Update(const double deltaTime);
	Manufacturer& GetManufacturer(int index);

private:
	Database<Goods> goodsDatabase;
	Database<Recipe> recipeDatabase;
	
	Float2 size;
	static constexpr float SECONDS_TO_HOURS = 1.0f;
	double clock = 0;
	int hour = 0;
	Factory_Manufacturer manufacturerFactory{};
	std::vector<Manufacturer> manufacturers;
	std::vector<Transporter> transporters;

	void NewHour();
	void CreateTransportRoute(int from, int to, GoodsType type, int transportCount);
};

