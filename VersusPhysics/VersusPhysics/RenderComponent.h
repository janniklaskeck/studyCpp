#pragma once
#include "Component.h"
#include "PhysicsComponent.h"
#include "Message.h"
#include "ChangePositionMessage.h"

#include <SFML/Graphics.hpp>

enum ShapeType
{
	NONE,
	BOX,
	CIRCLE
};

struct Shape
{
	float SizeX;
	float SizeY;
	float Radius;
	ShapeType Type;
	Shape(ShapeType _Type, float _SizeX, float _SizeY, float _Radius) :
		SizeX(_SizeX), SizeY(_SizeY), Radius(_Radius), Type(_Type)
	{
	}
	Shape() :
		SizeX(0), SizeY(0), Radius(0), Type(NONE)
	{
	}
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

	RenderComponent(Shape PrimitiveShape) :
		m_Shape(PrimitiveShape)
	{
	}

	RenderComponent(std::shared_ptr<sf::Texture> Texture) :
		Texture(Texture)
	{
		Sprite = std::make_unique<sf::Sprite>(*Texture.get());
	}

	void ProcessMessage(Message Msg)
	{
		if (MessageManager::GetTypeID(ChangePositionMessage::TYPE_NAME) == Msg.TypeID)
		{
			Position = Msg.VectorPayload;
		}
	};

private:
	std::shared_ptr<sf::Texture> Texture;
	std::unique_ptr<sf::Shape> m_RenderShape;
	Shape m_Shape;

	sf::Vector2f Position;
};