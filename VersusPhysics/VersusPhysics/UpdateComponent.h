#pragma once
#include "Component.h"

#include <functional>

typedef std::function<void(void)> UpdateCallback;

class UpdateComponent : public Component
{
public:

	virtual void Update() override;

	UpdateComponent(const UpdateCallback& Callback);
	~UpdateComponent();

private:
	UpdateCallback Callback;
};

