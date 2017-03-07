#pragma once
#include "Component.h"
#include "PhysicsComponent.h"
#include "Message.h"
#include "Vector2.hpp"

#include <SFML/Graphics.hpp>

class RenderComponent : public Component
{
public:

	std::unique_ptr<sf::Sprite> Sprite;
	virtual void Update() override;

	void Render(sf::RenderWindow* Window);

	RenderComponent(Shape PrimitiveShape);

	RenderComponent(std::shared_ptr<sf::Texture> Texture);

	virtual void ProcessMessage(Message Msg);

private:
	std::shared_ptr<sf::Texture> Texture;
	std::unique_ptr<sf::Shape> m_RenderShape;
	Shape _RenderShape;

	Vector2 Position;
};