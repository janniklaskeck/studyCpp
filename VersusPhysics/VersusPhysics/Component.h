#pragma once

class GameObject;
struct Message;

class Component
{
public:

	void Register(GameObject* Parent);

	virtual void Update()
	{
	};

	virtual void ProcessMessage(Message Msg) = 0;

	virtual ~Component()
	{

	}
protected:
	GameObject* Parent;
};

