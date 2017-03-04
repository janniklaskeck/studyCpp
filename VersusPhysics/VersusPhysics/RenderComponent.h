#pragma once
#include "Component.h"
#include "PhysicsComponent.h"
#include "Message.h"

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
	virtual void Update() override;

	void Render(sf::RenderWindow* Window);

	RenderComponent(Shape PrimitiveShape);

	RenderComponent(std::shared_ptr<sf::Texture> Texture);

	virtual void ProcessMessage(Message Msg);

private:
	std::shared_ptr<sf::Texture> Texture;
	std::unique_ptr<sf::Shape> m_RenderShape;
	Shape m_Shape;

	sf::Vector2f Position;
};