#include "GameObject.h"
#include "World.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "InputComponent.h"

void GameObject::Register(World* GameWorld)
{
	this->GameWorld = GameWorld;
}



void GameObject::Update()
{
	for (int i = 0; i < Components.size(); i++)
	{
		Component* Comp = Components[i].get();
		RenderComponent* RenderComp = dynamic_cast<RenderComponent*>(Comp);
		if (!RenderComp)
		{
			Comp->Update();
		}
	}
}

GameObject::GameObject(int ID) : ID(ID)
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

RenderComponent* GameObject::GetRenderComponent() const
{
	for (int i = 0; i < Components.size(); i++)
	{
		Component* Comp = Components[i].get();
		RenderComponent* PhysComp = dynamic_cast<RenderComponent*>(Comp);
		if (PhysComp)
		{
			return PhysComp;
		}
	}
	return nullptr;
}

InputComponent* GameObject::GetInputComponent() const
{
	for (int i = 0; i < Components.size(); i++)
	{
		Component* Comp = Components[i].get();
		InputComponent* PhysComp = dynamic_cast<InputComponent*>(Comp);
		if (PhysComp)
		{
			return PhysComp;
		}
	}
	return nullptr;
}
