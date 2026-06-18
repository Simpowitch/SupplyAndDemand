#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Renderer
{
public: 
	static Renderer* GetInstance();
	bool BeginFrame();
	void Draw(std::unique_ptr<sf::Drawable> drawable);
	void EndFrame();
	void Close();
private:
	Renderer();
	sf::Vector2u GetResolution();
	std::vector<std::unique_ptr<sf::Drawable>> drawables;
	sf::RenderWindow window;
};

struct RenderInstanceData
{
	sf::Vector2f size;
	sf::Color color;
};

