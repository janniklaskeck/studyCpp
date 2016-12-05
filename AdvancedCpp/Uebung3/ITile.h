#pragma once

#include <ostream>

class ITile
{

public:
	char displayChar;

	virtual bool isBlocking() = 0;
	virtual bool isGoal() = 0;

	virtual void render(std::ostream& stream) = 0;
};