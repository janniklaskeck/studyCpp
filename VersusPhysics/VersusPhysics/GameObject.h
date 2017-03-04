#pragma once
#include "Component.h"
#include "Message.h"

#include <memory>
#include <vector>
#include <queue>

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

	void Broadcast(Message& Msg);

	int ID;
private:
	std::vector<std::unique_ptr<Component>> Components;
	World* GameWorld;
	std::queue<Message> MessageQueue;
};

