#pragma once
#include "WorldView.h"

class ManufacturerView : public WorldView
{
public:
	ManufacturerView(const WorldModel* model, const Database<Goods>* goodsDatabase) : WorldView(model, goodsDatabase)
	{

	}

protected:
	void DrawSelf() override;
};

