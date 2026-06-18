#include "WorldView.h"
#include "Renderer.h"


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

		text.setPosition({ position.x - rectangleShape.getSize().x * 0.5f, position.y - rectangleShape.getSize().y * 0.5f - text.getCharacterSize()});
		text.setString("#" + std::to_string(++index) + " : " + manufacturer.GetSharedData()->name);
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

		text.setPosition({ position.x - rectangleShape.getSize().x * 0.5f, position.y - rectangleShape.getSize().y * 0.5f - text.getCharacterSize() });
		text.setString("#" + std::to_string(++index) + " : Transporter");
		renderer->Draw(text);
	}
}
