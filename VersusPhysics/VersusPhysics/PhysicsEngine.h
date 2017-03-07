#pragma once
#include "Manifold.hpp"
#include "PhysicsComponent.h"
#include "GameObject.h"

class PhysicsEngine
{
public:
	PhysicsEngine();
	~PhysicsEngine();

	void Register(GameObject* Object);

	void Update();

private:

	void DetectIntersection(Manifold _Manifold);
	void ResolveIntersection(Manifold _Manifold);

	bool DetectCircleVsCircle(Manifold& _Manifold);
	bool DetectCircleVsAABB(Manifold& _Manifold);
	bool DetectAABBVsAABB(Manifold& _Manifold);

	std::vector<PhysicsComponent*> Components;
};

