#pragma once

#include "Vector2D.h"

#include <ostream>

class ITile
{
public:

	Vector2D pos;
	char displayChar;

	virtual bool isBlocking() = 0;
	virtual bool isGoal() = 0;

	virtual void render(std::ostream& stream) = 0;
};