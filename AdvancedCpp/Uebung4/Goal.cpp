#include "Goal.h"

Goal::Goal(Vector2D pos)
{
	this->pos = pos;
	displayChar = 'G';
}


Goal::~Goal()
{
}

bool Goal::isBlocking()
{
	return false;
}

bool Goal::isGoal()
{
	return true;
}

void Goal::render(std::ostream& stream)
{
	stream << displayChar;
}
