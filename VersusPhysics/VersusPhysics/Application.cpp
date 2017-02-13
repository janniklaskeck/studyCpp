#include "Application.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "InputComponent.h"
#include "Constants.h"

#include <vector>

std::unique_ptr<World> Application::GameWorld = std::make_unique<World>();

void Application::GameLoop()
{
	sf::Clock Clock;
	while (m_Renderer.Window->isOpen())
	{
		sf::Time ElapsedTime = Clock.getElapsedTime();
		sf::Event event;
		while (m_Renderer.Window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_Renderer.Window->close();
			}
			else if (event.type == sf::Event::KeyPressed)
			{
				InputManager::HandleDownEvent(event);
			}
			else if (event.type == sf::Event::KeyReleased)
			{
				InputManager::HandleUpEvent(event);
			}
		}
		if (ElapsedTime.asMilliseconds() - GameWorld->GetElapsedTime() >= UPDATE_INTERVAL_MS)
		{
			GameWorld->Update();
			m_Renderer.Render(GameWorld->GetGameObjects());
		}
	}
}

void Application::Start()
{
	m_Renderer.Init();
	GameWorld = std::make_unique<World>();
}

void Application::Stop()
{
	m_Renderer.Shutdown();
}

Application::Application()
{
}


Application::~Application()
{
}

sf::Vector2u Application::GetWindowSize() const
{
	return m_Renderer.Window->getSize();
}
