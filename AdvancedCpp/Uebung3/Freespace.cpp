#include "Freespace.h"



Freespace::Freespace()
{
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
