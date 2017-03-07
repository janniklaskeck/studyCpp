#pragma once

#include "Shape.hpp"
#include "Vector2.hpp"

struct PhysicsState
{
	PhysicsState()
	{
	}
	PhysicsState(Vector2 Position, Vector2 Velocity)
	{
		this->Position = Position;
		this->Velocity = Velocity;
	}

	Vector2 Position;
	Vector2 Velocity;
};
