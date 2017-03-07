#pragma once
#include "Component.h"
#include "PhysicsDescription.h"
#include "PhysicsState.h"
#include "Constants.h"
#include "GameObject.h"
#include "World.h"

class PhysicsComponent : public Component
{
public:

	PhysicsComponent(PhysicsState _State, PhysicsDescription _Description)
	{
		this->Description = _Description;
		this->State = _State;
	}

	virtual void Update() override;

	void ProcessMessage(Message Msg);

	PhysicsState State;
	PhysicsDescription Description;
private:

	void Move();

	void CheckForCollisionAndResolve(World* GameWorld);

	bool IntersectsWith(PhysicsComponent* Other, sf::Rect<float>& IntersectionRect);

	Vector2 GetOverlapVector(PhysicsComponent* Other);

	void ResolveCollision(PhysicsComponent* OtherComp, Vector2 CollisionNormal);

	Vector2 GetPosition()
	{
		return State.Position;
	}

	Vector2 GetCenterAABB() const
	{
		return State.Position + (Description.PhysicsShape.Size * 0.5f);
	}
	sf::Rect<float> GetAABB()
	{
		sf::Rect<float> Rectangle;
		Rectangle.left = State.Position.X;
		Rectangle.top = State.Position.Y;
		Rectangle.width = Description.PhysicsShape.Size.X;
		Rectangle.height = Description.PhysicsShape.Size.Y;
		return Rectangle;
	}
};
