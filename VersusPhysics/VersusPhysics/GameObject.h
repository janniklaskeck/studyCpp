#pragma once
#include "Component.h"

#include <memory>
#include <vector>

class World;
class PhysicsComponent;
class RenderComponent;
class InputComponent;

class GameObject
{
public:

	void Register(World* GameWorld);

	void Update();

	GameObject(int ID);
	~GameObject();

	void AddComponent(Component* NewComponent);

	World* GetWorld() const
	{
		return GameWorld;
	}

	PhysicsComponent* GetPhyicsComponent() const;
	RenderComponent* GetRenderComponent() const;
	InputComponent* GetInputComponent() const;

	int ID;
private:
	std::vector<std::unique_ptr<Component>> Components;
	World* GameWorld;
};

