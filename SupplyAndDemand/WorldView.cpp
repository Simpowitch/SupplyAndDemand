#include "WorldView.h"

WorldView::WorldView(WorldModel* model, InputManager* inputManager, Database<Goods>* goodsDatabase) :
	model(model), inputManager(inputManager), interface(model, inputManager, goodsDatabase)
{

}

void WorldView::Draw()
{
	interface.Draw();
}
