#pragma once

#include "ITile.h"
#include "Wall.h"
#include "SharedPtr.h"
#include <vector>

class Util
{
public:
	static std::vector<std::vector<SharedPtr<ITile>>> loadBoard(char* fileName);
};

