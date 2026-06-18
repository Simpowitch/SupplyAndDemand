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

	PrintLine("-Time-");
	buffer << "Clock: " << model->clock << std::endl;
	buffer << "Hour: " << model->hour << std::endl;
	PrintLine("------");

	auto renderer = Renderer::GetInstance();
	for (const auto& manufacturer : model->manufacturers)
	{
		const auto& renderData = manufacturer.GetRenderData();
		auto shape = std::make_unique<sf::RectangleShape>();
		shape->setSize(renderData.size);
		shape->setFillColor(renderData.color);
		shape->setPosition({ manufacturer.GetPosition().x, manufacturer.GetPosition().y });
		renderer->Draw(std::move(shape));
	}

	for (const auto& transport : model->transporters)
	{
		const auto& renderData = transport.GetRenderData();

		auto shape = std::make_unique<sf::CircleShape>();
		shape->setRadius(renderData.size.x);
		shape->setFillColor(renderData.color);
		shape->setPosition({ transport.GetPosition().x, transport.GetPosition().y });
		renderer->Draw(std::move(shape));
	}
}
