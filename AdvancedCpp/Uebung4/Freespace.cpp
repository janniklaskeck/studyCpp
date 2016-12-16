#include "Freespace.h"

Freespace::Freespace(Vector2D pos)
{
	this->pos = pos;
	displayChar = '0';
}


Freespace::~Freespace()
{
}

bool Freespace::isBlocking()
{
	return false;
}

bool Freespace::isGoal()
{
	return false;
}

void Freespace::render(std::ostream& stream)
{
	stream << displayChar;
}
