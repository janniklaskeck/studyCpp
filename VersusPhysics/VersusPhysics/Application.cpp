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
		sf::Event Event;
		while (m_Renderer.Window->pollEvent(Event))
		{
			if (Event.type == sf::Event::Closed)
			{
				m_Renderer.Window->close();
			}
			else if (Event.type == sf::Event::KeyPressed)
			{
				InputManager::HandleDownEvent(Event);
			}
			else if (Event.type == sf::Event::KeyReleased)
			{
				InputManager::HandleUpEvent(Event);
			}
		}
		if (ElapsedTime.asMilliseconds() - GameWorld->GetElapsedTime() >= UPDATE_INTERVAL_MS)
		{
			GameWorld->Update();
			m_Renderer.Render(GameWorld->GetGameObjects());
		}
	}
}

void Application::Init()
{
	for (int Index = 0; Index < GameWorld->GetGameObjects().size(); Index++)
	{
		GameWorld->GetGameObjects()[Index]->Init();
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
