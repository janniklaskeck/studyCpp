#pragma once
#include "ITile.h"

class Freespace : public ITile
{
public:
	Freespace(Vector2D pos);
	~Freespace();

	virtual bool isBlocking() override;
	virtual bool isGoal() override;

	virtual void render(std::ostream& stream) override;
};

