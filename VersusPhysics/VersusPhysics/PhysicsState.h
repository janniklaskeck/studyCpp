#pragma once

#include <SFML/Graphics.hpp>

struct PhysicsState
{

	PhysicsState(sf::Vector2f Position, sf::Vector2f Velocity) : Position(Position), Velocity(Velocity)
	{
	}

	sf::Vector2f Position;
	sf::Vector2f Velocity;
};