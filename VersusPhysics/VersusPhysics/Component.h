#pragma once

class GameObject;

class Component
{
public:

	void Register(GameObject* Parent);

	virtual void Update()
	{
	};

	virtual ~Component()
	{

	}
protected:
	GameObject* Parent;
};

