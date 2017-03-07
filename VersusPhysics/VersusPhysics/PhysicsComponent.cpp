#include "Engine.hpp"

#include "PhysicsComponent.h"
#include "ChangePositionMessage.h"
#include "InputChangeMessage.hpp"
#include "Application.h"
#include "Manifold.hpp"

#include <stdio.h>
#include <glm/glm.hpp>
#include <algorithm>

void PhysicsComponent::Update()
{
	if (Description.Type == DYNAMIC)
	{
		Move();
	}
	Parent->Broadcast(ChangePositionMessage::Create(State.Position));
}

void PhysicsComponent::ProcessMessage(Message Msg)
{
	if (Msg.TypeID == MessageType::INPUT_CHANGE)
	{
		InputState _InputState = Msg.InputPayload;
		float Speed = 100.0f;
		if (_InputState.MoveUp)
		{
			State.Velocity.Y = -45.0f;
		}
		if (_InputState.MoveDown)
		{
			State.Velocity.Y = 35.0f;
		}
		if (_InputState.MoveRight)
		{
			State.Velocity.X = 35.0f;
		}
		if (_InputState.MoveLeft)
		{
			State.Velocity.X = -35.0f;
		}
	}
}

void PhysicsComponent::Move()
{
	Vector2 Forces(0, 10.0f);
	Vector2 Acceleration(Forces.X / Description.Mass, Forces.Y / Description.Mass);
	State.Velocity += Acceleration * UPDATE_INTERVAL_S;
	State.Position += State.Velocity * UPDATE_INTERVAL_S;

	CheckForCollisionAndResolve(Application::GameWorld.get());
}

void PhysicsComponent::CheckForCollisionAndResolve(World* GameWorld)
{
	for (int Index = 0; Index < GameWorld->GetGameObjects().size(); Index++)
	{
		std::shared_ptr<GameObject> OtherGameObject = GameWorld->GetGameObjects()[Index];
		PhysicsComponent* PhysComp = OtherGameObject->GetPhyicsComponent();
		if (PhysComp && PhysComp != this)
		{
			bool IntersectionDetected = false;
			Vector2 OverlapVector;
			sf::Rect<float> IntersectionRect;
			if (IntersectsWith(PhysComp, IntersectionRect))
			{
				IntersectionDetected = true;
				OverlapVector = GetOverlapVector(PhysComp);
				float Length = std::sqrt((OverlapVector.X*OverlapVector.X) + (OverlapVector.Y*OverlapVector.Y));
				Vector2 CollisionNormal = -1 * OverlapVector / Length;
				ResolveCollision(PhysComp, CollisionNormal);
				//State.Position += OverlapVector;
			}
		}
	}
}

bool PhysicsComponent::IntersectsWith(PhysicsComponent* Other, sf::Rect<float>& IntersectionRect)
{
	if (Description.PhysicsShape.Type == AABB)
	{
		sf::Rect<float> ThisAABB = GetAABB();
		sf::Rect<float> OtherAABB = Other->GetAABB();
		sf::Rect<float> Intersection;
		return ThisAABB.intersects(OtherAABB, Intersection);
	}
	else if (Description.PhysicsShape.Type == CIRCLE)
	{
		float Radii = (Description.PhysicsShape.Radius + Other->Description.PhysicsShape.Radius);
		float PosX = State.Position.X + Other->State.Position.X;
		float PosY = State.Position.Y + Other->State.Position.Y;
		Radii *= Radii;
		PosX *= PosX;
		PosY *= PosY;
		return Radii < (PosX + PosY);
	}
	return false;
}

Vector2 PhysicsComponent::GetOverlapVector(PhysicsComponent* PhysComp)
{
	Vector2 OverlapVector;

	float Left = PhysComp->GetPosition().X - (GetPosition().X + Description.PhysicsShape.Size.X);
	float Right = (PhysComp->GetPosition().X + PhysComp->Description.PhysicsShape.Size.X) - GetPosition().X;
	float Top = PhysComp->GetPosition().Y - (GetPosition().Y + Description.PhysicsShape.Size.Y);
	float Bottom = (PhysComp->GetPosition().Y + PhysComp->Description.PhysicsShape.Size.Y) - GetPosition().Y;

	if (Left > 0 || Right < 0 || Top > 0 || Bottom < 0)
	{
		return OverlapVector;
	}
	if (glm::abs(Left) < Right)
	{
		OverlapVector.X = Left;
	}
	else
	{
		OverlapVector.X = Right;
	}
	if (glm::abs(Top) < Bottom)
	{
		OverlapVector.Y = Top;
	}
	else
	{
		OverlapVector.Y = Bottom;
	}
	if (glm::abs(OverlapVector.X) < glm::abs(OverlapVector.Y))
	{
		OverlapVector.Y = 0;
	}
	else
	{
		OverlapVector.X = 0;
	}
	return OverlapVector;
}

void PhysicsComponent::ResolveCollision(PhysicsComponent * OtherComp, Vector2 CollisionNormal)
{
	Vector2 RelativeVelocity = OtherComp->State.Velocity - State.Velocity;
	float VelocityAlongNormal = RelativeVelocity.X * CollisionNormal.X + RelativeVelocity.Y * CollisionNormal.Y;
	if (VelocityAlongNormal > 0)
	{
		return;
	}
	float e = std::min(Description.Resitution, OtherComp->Description.Resitution);

	float ImpulseScalar = -(1 + e) * VelocityAlongNormal;
	ImpulseScalar /= 1 / Description.Mass + 1 / OtherComp->Description.Mass;

	Vector2 Impulse = ImpulseScalar * CollisionNormal;
	if (Description.Type == DYNAMIC)
	{
		State.Velocity -= 1 / Description.Mass * Impulse;
	}
	if (OtherComp->Description.Type == DYNAMIC)
	{
		OtherComp->State.Velocity += 1 / OtherComp->Description.Mass * Impulse;
	}
}
