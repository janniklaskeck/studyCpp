#include "Goal.h"



Goal::Goal()
{
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
