#pragma once
#include "WorldModel.h"
#include "Interface.h"
#include "Goods.h"
#include "Database.h"

class WorldView
{
public:
	WorldView(WorldModel* model, InputManager* inputManager, Database<Goods>* goodsDatabase);
	void Draw();

private:
	WorldModel* model;
	InputManager* inputManager;
	Interface interface; //TODO: Split into multiple screens/menus
};

