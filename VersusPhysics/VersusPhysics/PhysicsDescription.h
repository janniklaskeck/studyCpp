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
	float Mass = 1.0f;
	float Resitution = 1.0f;
	Shape PhysicsShape;
	
	PhysicsDescription& operator=(const PhysicsDescription& Other)
	{
		if (this != &Other)
		{
			this->Type = Other.Type;
			this->Mass = Other.Mass;
			this->Resitution = Other.Resitution;
			this->PhysicsShape = Other.PhysicsShape;
		}
		return *this;
	}
};
