#include "PhysicsComponent.h"
#include "ChangePositionMessage.h"
#include <stdio.h>
#include <glm/glm.hpp>
#include "Application.h"

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


}

void PhysicsComponent::Move()
{
	sf::Vector2f Forces(0, 10.0);
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

	float lx = glm::abs(GetCenter().x - Other->GetCenter().x);
	float sumx = (GetSize().x * 0.5f) + (Other->GetSize().x * 0.5f);

	float ly = glm::abs(GetCenter().y - Other->GetCenter().y);
	float sumy = (GetSize().y / 2.0f) + (Other->GetSize().y / 2.0f);

	return (lx <= sumx && ly <= sumy);
}

sf::Vector2f PhysicsComponent::GetOverlapVector(PhysicsComponent* PhysComp)
{
	sf::Vector2f OverlapVector;

	float Left = PhysComp->GetPosition().x - (GetPosition().x + GetSize().x);
	float Right = (PhysComp->GetPosition().x + PhysComp->GetSize().x) - GetPosition().x;
	float Top = PhysComp->GetPosition().y - (GetPosition().y + GetSize().y);
	float Bottom = (PhysComp->GetPosition().y + PhysComp->GetSize().y) - GetPosition().y;

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
