#pragma once
#include "InputManager.h"
#include "WorldModel.h"
#include "Database.h"
#include "Goods.h"

class Interface {
public:
	Interface(WorldModel* model, InputManager* inputManager, Database<Goods>* goodsDatabase);
	void ParseInput();
	void Draw();
private:
	WorldModel* model;
	InputManager* inputManager;
	Database<Goods>* goodsDatabase;
};
