#pragma once
#include <SFML/Graphics.hpp>

class Renderer
{
public: 
	static Renderer* GetInstance();
	bool BeginFrame();
	void Draw(const sf::Drawable& drawable);
	void EndFrame();
	void Close();
	const sf::Font& GetMainFont() const { return font; }
private:
	Renderer();
	sf::Vector2u GetResolution();
	sf::RenderWindow window;
	sf::Font font;
};

struct RenderInstanceData
{
	sf::Vector2f size;
	sf::Color color;
};

