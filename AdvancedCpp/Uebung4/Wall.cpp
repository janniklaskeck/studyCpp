#include "Wall.h"

Wall::Wall(Vector2D pos)
{
	this->pos = pos;
	displayChar = 'W';
}

Wall::~Wall()
{
}

bool Wall::isBlocking()
{
	return true;
}

bool Wall::isGoal()
{
	return false;
}

void Wall::render(std::ostream& stream)
{
	stream << displayChar;
}
