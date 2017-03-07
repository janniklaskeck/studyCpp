#include "RenderComponent.h"
#include "RenderMessage.hpp"
#include "ChangePositionMessage.h"
#include <stdio.h>
#include <SFML/System/Vector2.hpp>

void RenderComponent::Update()
{
}

void RenderComponent::Render(sf::RenderWindow * Window)
{
	float Width = _RenderShape.Size.X;
	float Height = _RenderShape.Size.Y;
	if (_RenderShape.Type == AABB)
	{
		m_RenderShape = std::make_unique<sf::RectangleShape>(sf::Vector2f(Width, Height));
		m_RenderShape->setFillColor(sf::Color(255, 0, 0));
	}
	else if (_RenderShape.Type == CIRCLE)
	{
		m_RenderShape = std::make_unique<sf::CircleShape>(Width);
		m_RenderShape->setFillColor(sf::Color(255, 0, 0));
	}

	if (_RenderShape.Type == NONE)
	{
		Sprite->setPosition(sf::Vector2f(Position.X, Position.Y));
		Window->draw(*Sprite.get());
	}
	else
	{
		m_RenderShape->setPosition(sf::Vector2f(Position.X, Position.Y));
		Window->draw(*m_RenderShape.get());
	}
}

RenderComponent::RenderComponent(Shape RenderShape) :
	_RenderShape(RenderShape)
{
}

RenderComponent::RenderComponent(std::shared_ptr<sf::Texture> _Texture) :
	Texture(_Texture)
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
