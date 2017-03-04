#pragma once
#include "Renderer.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "World.h"
#include <glm/glm.hpp>

class Application
{
public:

	void GameLoop();

	void Init();
	void Start();
	void Stop();

	Application();
	~Application();

	static std::unique_ptr<World> GameWorld;

	sf::Vector2u GetWindowSize() const;

private:
	Renderer m_Renderer;

};

