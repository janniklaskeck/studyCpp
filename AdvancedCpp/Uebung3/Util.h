#pragma once

#include "ITile.h"
#include "Wall.h"
#include <vector>

class Util
{
public:
	static std::vector<std::vector<char>> loadBoard(char* fileName);
};

