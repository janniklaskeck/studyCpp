#include "GameObject.h"
#include "World.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "InputComponent.h"

void GameObject::Register(World* GameWorld)
{
	this->GameWorld = GameWorld;
}

void GameObject::Init()
{
	for (int i = 0; i < Components.size(); i++)
	{
		Component* Comp = Components[i].get();
		Comp->Update();
	}
}

void GameObject::Update()
{
	while (!MessageQueue.empty())
	{
		Message Msg = MessageQueue.back();
		MessageQueue.pop();
		for (int i = 0; i < Components.size(); i++)
		{
			Component* Comp = Components[i].get();
			Comp->ProcessMessage(Msg);
		}
	}
	for (int i = 0; i < Components.size(); i++)
	{
		Component* Comp = Components[i].get();
		Comp->Update();
	}
}

PhysicsComponent* GameObject::GetPhyicsComponent() const
{
	for (int i = 0; i < Components.size(); i++)
	{
		Component* Comp = Components[i].get();
		PhysicsComponent* PhysComp = dynamic_cast<PhysicsComponent*>(Comp);
		if (PhysComp)
		{
			return PhysComp;
		}
	}
	return nullptr;
}

GameObject::GameObject(int _ID) : ID(_ID)
{
}

GameObject::~GameObject()
{
}

void GameObject::AddComponent(Component* NewComponent)
{
	Components.push_back(std::unique_ptr<Component>(NewComponent));
	NewComponent->Register(this);
}

void GameObject::Broadcast(Message& Msg)
{
	MessageQueue.push(Msg);
}
