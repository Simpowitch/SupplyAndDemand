#include "Interface.h"
#include <iostream>

Interface::Interface(WorldModel* model, InputManager* inputManager, Database<Goods>* goodsDatabase) :
	model(model), inputManager(inputManager), goodsDatabase(goodsDatabase)
{
}

void Interface::ParseInput()
{

}

void Interface::Draw()
{
	//Print state
	system("cls");
	std::cout << "-Manufacturers-" << std::endl;

	int index = -1;
	for (const auto& manufacturer : model->manufacturers)
	{
		const auto* data = manufacturer.GetSharedData();
		std::cout << "(" << ++index << ") " << data->name << std::endl;
		const auto position = manufacturer.GetPosition();
		std::cout << "-Position: " << position.x << " " << position.y << std::endl;
		std::cout << "-Progress:" << manufacturer.GetProductionProgress() << std::endl;
		std::cout << "-Has Power: " << manufacturer.GetPowerState() << std::endl;
		std::cout << "-Storage-" << std::endl;
		const auto& storage = manufacturer.GetStorage();
		for (const auto& storageElement : storage)
		{
			auto goods = goodsDatabase->TryGetElement(storageElement.first);
			std::string name = goods == nullptr ? "Unknown" : goods->name;
			std::cout << name << " " << storageElement.second << std::endl;
		}
		std::cout << "-------------------" << std::endl;
	}

	index = -1;
	std::cout << "-Transporters-" << std::endl;
	for (const auto& transporter : model->transporters)
	{
		std::cout << "Transporter (" << ++index << ")" << std::endl;
		auto position = transporter.GetPosition();
		std::cout << "-Position: " << position.x << " " << position.y << std::endl;
		std::cout << "-State: " << ToString(transporter.GetCurrentStatus()) << std::endl;
		const HaulJob job = transporter.GetJob();
		auto goods = goodsDatabase->TryGetElement(job.goodsId);
		std::string name = goods == nullptr ? "Unknown" : goods->name;
		std::cout << "-Last/Current Job: " << "Delivering " << name << " x" << job.count << " from #" << job.pickupId << " to #" << job.deliveryId << std::endl;
		goods = goodsDatabase->TryGetElement(transporter.GetGoodsId());
		name = goods == nullptr ? "Unknown" : goods->name;
		std::cout << "-Cargo: " << name << " x" << transporter.GetGoodsCount() << std::endl;
		std::cout << "-Speed: " << transporter.GetSpeed() << std::endl;
		std::cout << "-------------------" << std::endl;
	}

	std::cout << "Power balance: " << model->currentPowerBalance << std::endl;

	std::cout << "-Time-" << std::endl;
	std::cout << "Clock: " << model->clock << std::endl;
	std::cout << "Hour: " << model->currentPowerBalance << std::endl;
}