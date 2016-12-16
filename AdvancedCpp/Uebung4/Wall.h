#pragma once
#include "ITile.h"

class Wall : public ITile
{

public:
	Wall(Vector2D pos);
	~Wall();

	virtual bool isBlocking() override;
	virtual bool isGoal() override;

	virtual void render(std::ostream& stream) override;
};

