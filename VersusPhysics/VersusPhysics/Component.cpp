#include "Component.h"
#include "GameObject.h"

void Component::Register(GameObject* Parent)
{
	this->Parent = Parent;
}
