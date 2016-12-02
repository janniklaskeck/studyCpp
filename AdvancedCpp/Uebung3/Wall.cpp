#include "Wall.h"

Wall::Wall()
{
	displayChar = 'X';
}

Wall::~Wall()
{
}

bool Wall::isBlocking()
{
	return false;
}

bool Wall::isGoal()
{
	return false;
}

void Wall::render(std::ostream stream)
{

}
