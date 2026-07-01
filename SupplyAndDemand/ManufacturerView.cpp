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
		buffer << "-Input Storage-" << std::endl;
		for (size_t i = 0; i < manufacturer.GetInputSlotCount(); i++)
		{
			const auto& storageSlot = manufacturer.GetInputInventory(i);
			auto goods = goodsDatabase->TryGetElement(storageSlot.goodsId);
			std::string name = goods == nullptr ? "Unknown" : goods->name;
			buffer << name << " " << storageSlot.goods.current << std::endl;
		}
		buffer << "-Output Storage-" << std::endl;
		for (size_t i = 0; i < manufacturer.GetOutputSlotCount(); i++)
		{
			const auto& storageSlot = manufacturer.GetOutputInventory(i);
			auto goods = goodsDatabase->TryGetElement(storageSlot.goodsId);
			std::string name = goods == nullptr ? "Unknown" : goods->name;
			buffer << name << " " << storageSlot.goods.current << std::endl;
		}
		PrintLine("-------------------");
	}
}