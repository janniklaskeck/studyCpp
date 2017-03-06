#include "Engine.hpp"

#include "PhysicsComponent.h"
#include "ChangePositionMessage.h"
#include "InputChangeMessage.hpp"
#include "Application.h"

#include <stdio.h>
#include <glm/glm.hpp>

void PhysicsComponent::Update()
{
	if (Description.Type == DYNAMIC)
	{
		Move();
		//LOG("Pos: %f | %f\n", State.Position.x, State.Position.y);
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
			State.Velocity.y = -45.0f;
		}
		if (_InputState.MoveDown)
		{
			State.Velocity.y = 35.0f;
		}
		if (_InputState.MoveRight)
		{
			State.Velocity.x = 35.0f;
		}
		if (_InputState.MoveLeft)
		{
			State.Velocity.x = -35.0f;
		}
	}
}

void PhysicsComponent::Move()
{
	sf::Vector2f Forces(0, 10.0f);
	sf::Vector2f Acceleration(Forces.x / Description.Mass, Forces.y / Description.Mass);
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
			sf::Vector2f OverlapVector;
			if (IntersectsWith(PhysComp))
			{
				IntersectionDetected = true;
				OverlapVector = GetOverlapVector(PhysComp);
				State.Position += OverlapVector;
			}

			if (IntersectionDetected)
			{
			}
		}
	}
}

bool PhysicsComponent::IntersectsWith(PhysicsComponent* Other)
{
	if (Description.PhysicsShape.Type == AABB)
	{
		float lx = glm::abs(GetCenterAABB().x - Other->GetCenterAABB().x);
		float sumx = (Description.PhysicsShape.Size.x * 0.5f) + (Other->Description.PhysicsShape.Size.x * 0.5f);

		float ly = glm::abs(GetCenterAABB().y - Other->GetCenterAABB().y);
		float sumy = (Description.PhysicsShape.Size.y* 0.5f) + (Other->Description.PhysicsShape.Size.y * 0.5f);

		return (lx <= sumx && ly <= sumy);
	}
	else if (Description.PhysicsShape.Type == CIRCLE)
	{
		float Radii = (Description.PhysicsShape.Radius + Other->Description.PhysicsShape.Radius);
		Radii *= Radii;
		float PosX = State.Position.x + Other->State.Position.x;
		float PosY = State.Position.y + Other->State.Position.y;
		return Radii < (PosX*PosX) + (PosY*PosY);
	}
	return false;
}

sf::Vector2f PhysicsComponent::GetOverlapVector(PhysicsComponent* PhysComp)
{
	sf::Vector2f OverlapVector;

	float Left = PhysComp->GetPosition().x - (GetPosition().x + Description.PhysicsShape.Size.x);
	float Right = (PhysComp->GetPosition().x + PhysComp->Description.PhysicsShape.Size.x) - GetPosition().x;
	float Top = PhysComp->GetPosition().y - (GetPosition().y + Description.PhysicsShape.Size.y);
	float Bottom = (PhysComp->GetPosition().y + PhysComp->Description.PhysicsShape.Size.y) - GetPosition().y;

	if (Left > 0 || Right < 0 || Top > 0 || Bottom < 0)
	{
		return OverlapVector;
	}
	if (glm::abs(Left) < Right)
	{
		OverlapVector.x = Left;
	}
	else
	{
		OverlapVector.x = Right;
	}
	if (glm::abs(Top) < Bottom)
	{
		OverlapVector.y = Top;
	}
	else
	{
		OverlapVector.y = Bottom;
	}
	if (glm::abs(OverlapVector.x) < glm::abs(OverlapVector.y))
	{
		OverlapVector.y = 0;
	}
	else
	{
		OverlapVector.x = 0;
	}
	return OverlapVector;
}
