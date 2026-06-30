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
	buffer << "Population: " << model->population << std::endl;

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
		infoText += "\nStorage";
		const auto& storage = manufacturer.GetStorage();
		for (const auto& storageElement : storage)
		{
			auto goods = goodsDatabase->TryGetElement(storageElement.first);
			std::string name = goods == nullptr ? "Unknown" : goods->name;
			infoText += "\n" + name + " " + std::to_string(storageElement.second);
		}
		text.setString(infoText);
		text.setPosition({ position.x - rectangleShape.getSize().x * 0.5f, position.y - rectangleShape.getSize().y * 0.5f - text.getCharacterSize() });
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
		std::string status = ToString(transporter.GetCurrentStatus());
		infoText += "\n" + status;
		const HaulJob job = transporter.GetJob();
		auto goods = goodsDatabase->TryGetElement(job.goodsId);
		std::string name = goods == nullptr ? "Unknown" : goods->name;
		infoText += "\nLast/Current Job: Delivering " + name + " x" + std::to_string(job.count) + " from #" + std::to_string(job.pickupId) + " to #" + std::to_string(job.deliveryId);
		infoText += "\nCargo: " + name + " x" + std::to_string(transporter.GetGoodsCount());
		infoText += "\nSpeed: " + std::to_string(transporter.GetSpeed());

		text.setString(infoText);
		text.setPosition({ position.x - rectangleShape.getSize().x * 0.5f, position.y - rectangleShape.getSize().y * 0.5f - text.getCharacterSize() });
		renderer->Draw(text);
	}

}
