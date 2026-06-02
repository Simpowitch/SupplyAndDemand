#include "WorldView.h"


WorldView::WorldView(const WorldModel* model, const Database<Goods>* goodsDatabase) :
	model(model), goodsDatabase(goodsDatabase)
{
	
}

void WorldView::DrawSelf()
{
	View::DrawSelf();

	buffer << "Power balance: " << model->currentPowerBalance << std::endl;

	PrintLine("-Time-");
	buffer << "Clock: " << model->clock << std::endl;
	buffer << "Hour: " << model->hour << std::endl;
	PrintLine("------");
}
