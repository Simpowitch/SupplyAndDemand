#pragma once
#include "WorldView.h"

class TransporterView : public WorldView
{
public:
	TransporterView(const WorldModel* model, const Database<Goods>* goodsDatabase) : WorldView(model, goodsDatabase)
	{

	}

protected:
	void DrawSelf() override;
};

