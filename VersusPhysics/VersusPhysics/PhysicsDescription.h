#pragma once
#include "Shape.hpp"

enum PhysicsType
{
	STATIC,
	DYNAMIC
};

struct PhysicsDescription
{
public:

	PhysicsDescription()
	{
	}
	~PhysicsDescription()
	{
	};

	PhysicsType Type = STATIC;
	float Mass = 1.0;
	Shape PhysicsShape;
};
