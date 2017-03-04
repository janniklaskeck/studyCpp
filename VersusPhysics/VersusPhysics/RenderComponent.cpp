#include "RenderComponent.h"
#include "RenderMessage.hpp"
#include "ChangePositionMessage.h"
#include <stdio.h>

void RenderComponent::Update()
{
}

void RenderComponent::Render(sf::RenderWindow * Window)
{
	float Width = m_Shape.SizeX;
	float Height = m_Shape.SizeY;
	if (m_Shape.Type == BOX)
	{
		m_RenderShape = std::make_unique<sf::RectangleShape>(sf::Vector2f(Width, Height));
		m_RenderShape->setFillColor(sf::Color(255, 0, 0));
	}
	else if (m_Shape.Type == CIRCLE)
	{
		m_RenderShape = std::make_unique<sf::CircleShape>(Width);
		m_RenderShape->setFillColor(sf::Color(255, 0, 0));
	}

	if (m_Shape.Type == NONE)
	{
		Sprite->setPosition(Position);
		Window->draw(*Sprite.get());
	}
	else
	{
		m_RenderShape->setPosition(Position);
		Window->draw(*m_RenderShape.get());
	}
}

RenderComponent::RenderComponent(Shape PrimitiveShape) :
	m_Shape(PrimitiveShape)
{
}

RenderComponent::RenderComponent(std::shared_ptr<sf::Texture> Texture) :
	Texture(Texture)
{
	Sprite = std::make_unique<sf::Sprite>(*Texture.get());
}

void RenderComponent::ProcessMessage(Message Msg)
{
	if (MessageType::POSITION_CHANGE == Msg.TypeID)
	{
		Position = Msg.VectorPayload;
	}
	else if (MessageType::DO_RENDER == Msg.TypeID)
	{
		if (Msg.WindowPtrPayload)
		{
			Render(Msg.WindowPtrPayload);
		}
	}
};
