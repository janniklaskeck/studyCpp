#include "Player.h"
#include "Board.h"

Player::Player(SharedPtr<Board> board, Vector2D startPos)
{
	m_board = board;
	pos = startPos;
}

Player::~Player()
{
}

bool Player::move(Vector2D nextPos)
{
	if (!m_board->getField(nextPos)->isBlocking())
	{
		pos = nextPos;
		return true;
	}
	return false;
}

bool Player::attack()
{
	return false;
}
