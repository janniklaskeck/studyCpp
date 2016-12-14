#pragma once
#include "ITile.h"

class Wall : public ITile
{

public:
	Wall();
	~Wall();

	virtual bool isBlocking() override;
	virtual bool isGoal() override;

	virtual void render(std::ostream& stream) override;
};

