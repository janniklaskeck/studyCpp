#pragma once
#include "Component.h"
#include "PhysicsComponent.h"

#include <SFML/Graphics.hpp>

enum Shape
{
	NONE,
	BOX,
	CIRCLE
};

class RenderComponent : public Component
{
public:

	std::unique_ptr<sf::Sprite> Sprite;
	virtual void Update() override
	{
	}

	void Render(sf::RenderWindow* Window)
	{
		float Width = Parent->GetPhyicsComponent()->GetSize().x;
		float Height = Parent->GetPhyicsComponent()->GetSize().y;
		if (m_Shape == BOX)
		{
			m_RenderShape = std::make_unique<sf::RectangleShape>(sf::Vector2f(Width, Height));
			m_RenderShape->setFillColor(sf::Color(255, 0, 0));
		}
		else if (m_Shape == CIRCLE)
		{
			m_RenderShape = std::make_unique<sf::CircleShape>(Width);
			m_RenderShape->setFillColor(sf::Color(255, 0, 0));
		}

		if (m_Shape == NONE)
		{
			Sprite->setPosition(Parent->GetPhyicsComponent()->GetPosition());
			Window->draw(*Sprite.get());
		}
		else
		{
			m_RenderShape->setPosition(Parent->GetPhyicsComponent()->GetPosition());
			Window->draw(*m_RenderShape.get());
		}
	}

	RenderComponent(Shape PrimitiveShape) :
		m_Shape(PrimitiveShape)
	{
	}

	RenderComponent(std::shared_ptr<sf::Texture> Texture) :
		Texture(Texture)
	{
		Sprite = std::make_unique<sf::Sprite>(*Texture.get());
	}
private:
	std::shared_ptr<sf::Texture> Texture;
	std::unique_ptr<sf::Shape> m_RenderShape;
	Shape m_Shape = NONE;
};