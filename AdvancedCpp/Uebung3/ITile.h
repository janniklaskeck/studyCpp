#pragma once

#include <ostream>

class ITile
{
protected:
	char displayChar;

public:


	virtual bool isBlocking() = 0;
	virtual bool isGoal() = 0;

	virtual void render(std::ostream stream) = 0;
};