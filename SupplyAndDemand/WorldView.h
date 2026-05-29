#pragma once
#include "View.h"
#include "WorldModel.h"
#include "Goods.h"
#include "Database.h"

class WorldView : public View
{
public:
	WorldView(const WorldModel* model, const Database<Goods>* goodsDatabase);

protected:
	void DrawSelf() override;
	const WorldModel* model;
	const Database<Goods>* goodsDatabase;
};

