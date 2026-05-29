#include "ManufacturerView.h"

void ManufacturerView::DrawSelf()
{
	WorldView::DrawSelf();

	PrintLine("-Manufacturers-");
	int index = -1;
	for (const auto& manufacturer : model->manufacturers)
	{
		const auto* data = manufacturer.GetSharedData();
		buffer << "(" << ++index << ") " << data->name << std::endl;
		const auto position = manufacturer.GetPosition();
		buffer << "-Position: " << position.x << " " << position.y << std::endl;
		buffer << "-Progress:" << manufacturer.GetProductionProgress() << std::endl;
		buffer << "-Has Power: " << manufacturer.GetPowerState() << std::endl;
		buffer << "-Storage-" << std::endl;
		const auto& storage = manufacturer.GetStorage();
		for (const auto& storageElement : storage)
		{
			auto goods = goodsDatabase->TryGetElement(storageElement.first);
			std::string name = goods == nullptr ? "Unknown" : goods->name;
			buffer << name << " " << storageElement.second << std::endl;
		}
		PrintLine("-------------------");
	}
}