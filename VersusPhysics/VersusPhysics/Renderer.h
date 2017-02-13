#pragma once
#include "GameObject.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Renderer
{
public:

	const int WINDOW_WIDTH = 1280;
	const int WINDOW_HEIGHT = 720;

	std::unique_ptr<sf::RenderWindow> Window;

	bool Init();

	void Shutdown();

	void Render(std::vector<std::shared_ptr<GameObject>>& Objects);

	Renderer();
	~Renderer();

private:
	std::unique_ptr<sf::View> LeftView;
	std::unique_ptr<sf::View> RightView;
};

