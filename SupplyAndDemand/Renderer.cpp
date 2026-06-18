#include "Renderer.h"
#include "Settings.h"

Renderer* instance = nullptr;

Renderer::Renderer() :
	drawables{1024},
	window(sf::VideoMode(GetResolution()), settings::GetApplicationName(), sf::Style::Default, sf::State::Windowed)
{

}

Renderer* Renderer::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Renderer();
	}

	return instance;
}

bool Renderer::BeginFrame()
{
	drawables.clear();
	window.clear();

	if (!window.isOpen())
	{
		return false;
	}

	return true;
}

void Renderer::Draw(std::unique_ptr<sf::Drawable> drawable)
{
	drawables.push_back(std::move(drawable));
}

void Renderer::EndFrame()
{
	for (const auto& drawable : drawables)
	{
		window.draw(*drawable);
	}
	window.display();

	while (const std::optional event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			window.close();
		}
	}
}

void Renderer::Close()
{
	window.close();
}

sf::Vector2u Renderer::GetResolution()
{
	const auto resolution = settings::GetResolution();
	return { resolution.first, resolution.second };
}

