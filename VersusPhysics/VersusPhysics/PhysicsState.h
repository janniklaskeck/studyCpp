#pragma once

#include "Shape.hpp"
#include <SFML/System/Vector2.hpp>

struct PhysicsState
{
	PhysicsState(sf::Vector2f Position, sf::Vector2f Velocity) : Position(Position), Velocity(Velocity)
	{
	}

	sf::Vector2f Position;
	sf::Vector2f Velocity;
};
