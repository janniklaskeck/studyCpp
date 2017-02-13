#pragma once
#include <SFML/Graphics.hpp>

enum PhysicsType
{
	STATIC,
	DYNAMIC
};

struct PhysicsDescription
{
public:

	PhysicsType Type = STATIC;
	float Mass = 1.0;
	sf::Vector2f Size = sf::Vector2f(0.0f, 0.0f);

};