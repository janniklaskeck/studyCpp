#pragma once
#include "SharedPtr.h"
#include "Vector2D.h"

class Board;

class Player
{
private:

	//SharedPtr<Board> m_board;

public:

	Vector2D pos;
	Vector2D dir;
	Player(SharedPtr<Board> m_board, Vector2D startPos);
	~Player();

	bool move(Vector2D nextPos);
	bool attack();
};

