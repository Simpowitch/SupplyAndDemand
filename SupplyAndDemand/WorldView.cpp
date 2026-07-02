#include "WorldView.h"
#include "Renderer.h"
#include <string>
#include "Transporter.h"


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

	auto renderer = Renderer::GetInstance();
	sf::RectangleShape rectangleShape;

	const auto& font = renderer->GetMainFont();
	sf::Text text(font);
	text.setCharacterSize(14);
	text.setFillColor(sf::Color::White);

	for (const auto& city : model->cities)
	{
		const auto& renderData = city.GetRenderData();
		const auto& position = city.GetPosition();
		rectangleShape.setSize(renderData.size);
		rectangleShape.setFillColor(renderData.color);
		rectangleShape.setPosition({ position.x,position.y });
		rectangleShape.setOrigin({ rectangleShape.getSize().x * 0.5f,rectangleShape.getSize().y * 0.5f });
		renderer->Draw(rectangleShape);

		std::string infoText = city.GetName();
		infoText += "\nPopulation: " + std::to_string(city.GetPopulation());
		const auto inputCount = city.GetInputSlotCount();
		if (inputCount > 0)
		{
			infoText += "\nInput Storage: ";
			for (size_t i = 0; i < inputCount; i++)
			{
				const auto& storageSlot = city.GetInputInventory(i);
				auto goods = goodsDatabase->TryGetElement(storageSlot.goodsId);
				std::string name = goods == nullptr ? "Unknown" : goods->name;
				infoText += "\n" + name + " x" + std::to_string(storageSlot.goods.current) + " (" + std::to_string(storageSlot.goods.reserved) + ")";
			}
		}
		text.setString(infoText);
		text.setPosition({ position.x, position.y + rectangleShape.getSize().y * 0.5f});
		renderer->Draw(text);
	}

	int index = -1;
	for (const auto& manufacturer : model->manufacturers)
	{
		const auto& renderData = manufacturer.GetRenderData();
		const auto& position = manufacturer.GetPosition();
		rectangleShape.setSize(renderData.size);
		rectangleShape.setFillColor(renderData.color);
		rectangleShape.setPosition({ position.x,position.y });
		rectangleShape.setOrigin({ rectangleShape.getSize().x * 0.5f,rectangleShape.getSize().y * 0.5f });
		renderer->Draw(rectangleShape);

		std::string infoText = "#" + std::to_string(++index) + " : " + manufacturer.GetSharedData()->name;
		infoText += "\nPower: " + std::to_string(manufacturer.GetPowerState());
		infoText += "\nProgress: " + std::to_string(manufacturer.GetProductionProgress());

		const auto inputCount = manufacturer.GetInputSlotCount();
		if (inputCount > 0)
		{
			infoText += "\nInput Storage: ";
			for (size_t i = 0; i < inputCount; i++)
			{
				const auto& storageSlot = manufacturer.GetInputInventory(i);
				auto goods = goodsDatabase->TryGetElement(storageSlot.goodsId);
				std::string name = goods == nullptr ? "Unknown" : goods->name;
				infoText += "\n" + name + " x" + std::to_string(storageSlot.goods.current) + " (" + std::to_string(storageSlot.goods.reserved) + ")";
			}
		}

		const auto outputCount = manufacturer.GetOutputSlotCount();
		if (outputCount > 0)
		{
			infoText += "\nOutput Storage: ";
			for (size_t i = 0; i < outputCount; i++)
			{
				const auto& storageSlot = manufacturer.GetOutputInventory(i);
				auto goods = goodsDatabase->TryGetElement(storageSlot.goodsId);
				std::string name = goods == nullptr ? "Unknown" : goods->name;
				infoText += "\n" + name + " x" + std::to_string(storageSlot.goods.current) + " (" + std::to_string(storageSlot.goods.reserved) + ")";
			}
		}
		
		text.setString(infoText);
		text.setPosition({ position.x, position.y + rectangleShape.getSize().y * 0.5f});
		renderer->Draw(text);
	}

	index = -1;
	for (const auto& transporter : model->transporters)
	{
		const auto& renderData = transporter.GetRenderData();
		const auto& position = transporter.GetPosition();
		rectangleShape.setSize(renderData.size);
		rectangleShape.setFillColor(renderData.color);
		rectangleShape.setPosition({ position.x, position.y });
		rectangleShape.setOrigin({ rectangleShape.getSize().x * 0.5f,rectangleShape.getSize().y * 0.5f });
		renderer->Draw(rectangleShape);

		std::string infoText = "#" + std::to_string(++index) + " : Transporter";
		const auto& status = transporter.GetCurrentStatus();
		std::string status_text = ToString(status);
		infoText += "\n" + status_text;
		const HaulJob job = transporter.GetJob();
		auto goods = goodsDatabase->TryGetElement(job.goodsId);
		std::string name = goods == nullptr ? "Unknown" : goods->name;
		if (status != Status::Inactive)
		{
			infoText += "\nLast/Current Job: Delivering " + name + " x" + std::to_string(job.goodsCount) + " from " + job.provider->GetName() + " to " + job.requester->GetName();
		}
		infoText += "\nCargo: " + name + " x" + std::to_string(transporter.GetGoodsCount());
		infoText += "\nSpeed: " + std::to_string(transporter.GetSpeed());

		text.setString(infoText);
		text.setPosition({ position.x, position.y + rectangleShape.getSize().y * 0.5f});
		renderer->Draw(text);
	}

}
