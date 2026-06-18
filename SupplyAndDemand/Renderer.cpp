#include "Renderer.h"
#include "Settings.h"

Renderer* instance = nullptr;

Renderer::Renderer() :
	window(sf::VideoMode(GetResolution()), settings::GetApplicationName(), sf::Style::Default, sf::State::Windowed),
	font(settings::ResolveGameAssetPath("resources/fonts/OpenSans-Regular.ttf"))
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
	window.clear();

	if (!window.isOpen())
	{
		return false;
	}

	return true;
}

void Renderer::Draw(const sf::Drawable& drawable)
{
	window.draw(drawable);
}

void Renderer::EndFrame()
{
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

