#include "Renderer.h"
#include "RenderComponent.h"

#include <stdio.h>

bool Renderer::Init()
{
	Window = std::make_unique<sf::RenderWindow>(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "VersusPhysics v1.0");
	Window->setFramerateLimit(60);
	
	float Width = static_cast<float>(WINDOW_WIDTH);
	float Height = static_cast<float>(WINDOW_HEIGHT);

	LeftView = std::make_unique<sf::View>(sf::FloatRect(0.0f, 0.0f, Width * 0.5f, Height));
	LeftView->setViewport(sf::FloatRect(0.0f, 0.0f, 0.5f, 1.0f));
	RightView = std::make_unique<sf::View>(sf::FloatRect(Width * 0.5f, 0.0f, Width * 0.5f, Height));
	RightView->setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 1.0f));
	return false;
}

void Renderer::Shutdown()
{
}

void Renderer::Render(std::vector<std::shared_ptr<GameObject>>& GameObjects)
{
	Window->clear();

	for (int i = 0; i < GameObjects.size(); i++)
	{
		GameObject* Object = GameObjects[i].get();
		if (Object)
		{
			RenderComponent* RenderComp = Object->GetRenderComponent();
			if (RenderComp)
			{
				RenderComp->Update();
				RenderComp->Render(Window.get());
			}
		}
	}
	Window->display();
}

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}
