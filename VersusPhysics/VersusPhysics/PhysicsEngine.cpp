#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine()
{
}

PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::Register(GameObject* Object)
{
}

void PhysicsEngine::Update()
{
	for (int Index = 0; Index < Components.size(); Index++)
	{
		PhysicsComponent* Current = Components[Index];
		for (int OtherIndex = 0; OtherIndex < Components.size(); OtherIndex++)
		{
			PhysicsComponent* Other = Components[OtherIndex];
			if (Other == Current)
			{
				continue;
			}
			Manifold _Manifold;
			_Manifold.CompA = Current;
			_Manifold.CompB = Other;
			DetectIntersection(_Manifold);
		}
	}
}

void PhysicsEngine::DetectIntersection(Manifold _Manifold)
{
	ShapeType TypeA = _Manifold.CompA->Description.PhysicsShape.Type;
	ShapeType TypeB = _Manifold.CompB->Description.PhysicsShape.Type;
	if (TypeA == AABB && TypeB == AABB)
	{
		DetectAABBVsAABB(_Manifold);
	}
	else if (TypeA == CIRCLE && TypeB == CIRCLE)
	{
		DetectCircleVsCircle(_Manifold);
	}
	else if ((TypeA == AABB && TypeB == CIRCLE) || (TypeA == CIRCLE && TypeB == AABB))
	{
		DetectCircleVsAABB(_Manifold);
	}
}

void PhysicsEngine::ResolveIntersection(Manifold _Manifold)
{
}

bool PhysicsEngine::DetectCircleVsCircle(Manifold& _Manifold)
{
	Vector2 AToB = _Manifold.CompB->State.Position - _Manifold.CompA->State.Position;;
	float RadiiSquared = _Manifold.CompA->Description.PhysicsShape.Radius + _Manifold.CompB->Description.PhysicsShape.Radius;
	RadiiSquared *= RadiiSquared;

	if (0 > RadiiSquared) // AToB squared
	{
		return false;
	}

	float Distance = AToB.X; // length sqrt
	if (Distance != 0)
	{
		_Manifold.Penetration = RadiiSquared - Distance;
		
	}

	return false;
}

bool PhysicsEngine::DetectCircleVsAABB(Manifold& _Manifold)
{
	return false;
}

bool PhysicsEngine::DetectAABBVsAABB(Manifold& _Manifold)
{
	return false;
}
