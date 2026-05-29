#include "WorldView.h"


WorldView::WorldView(const WorldModel* model, const Database<Goods>* goodsDatabase) :
	model(model), goodsDatabase(goodsDatabase)
{
	
}

void WorldView::DrawSelf()
{
	View::DrawSelf();

	std::cout << "Power balance: " << model->currentPowerBalance << std::endl;

	std::cout << "-Time-" << std::endl;
	std::cout << "Clock: " << model->clock << std::endl;
	std::cout << "Hour: " << model->currentPowerBalance << std::endl;
}
