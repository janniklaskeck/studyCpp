#pragma once
#include "ITile.h"

class Freespace : public ITile
{
public:
	Freespace();
	~Freespace();

	virtual bool isBlocking() override;
	virtual bool isGoal() override;

	virtual void render(std::ostream& stream) override;
};

