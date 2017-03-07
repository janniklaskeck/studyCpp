#pragma once
#include "PhysicsComponent.h"

#include "Vector2.hpp"

struct Manifold
{
	PhysicsComponent* CompA;
	PhysicsComponent* CompB;
	float Penetration;
	Vector2 Normal;
};
