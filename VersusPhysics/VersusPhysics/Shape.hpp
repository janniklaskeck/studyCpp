#pragma once
#include <SFML/System/Vector2.hpp>

enum ShapeType
{
	NONE,
	AABB,
	CIRCLE
};

struct Shape
{
	Shape()
	{
	}
	~Shape()
	{
	}

	ShapeType Type;
	union
	{
		float Radius;
		sf::Vector2f Size;
	};
};
