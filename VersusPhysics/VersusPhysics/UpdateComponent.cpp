#include "UpdateComponent.h"



void UpdateComponent::Update()
{
	Callback();
}

UpdateComponent::UpdateComponent(const UpdateCallback& Callback)
{
	this->Callback = Callback;
}


UpdateComponent::~UpdateComponent()
{
}
