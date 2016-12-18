#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Vector2D.h"
#include "ITile.h"
#include "Player.h"
#include "UniquePtr.h"
#include "SharedPtr.h"

class Board
{

private:
	std::vector<std::vector<SharedPtr<ITile>>> m_map;
	UniquePtr<Player> m_player;

	bool move(const char direction);

public:
	Board();
	~Board()
	{
	};
	SharedPtr<ITile> getField(const Vector2D position);

	void render();
};

