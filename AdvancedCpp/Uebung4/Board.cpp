#include "Board.h"

#include <conio.h>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <sstream>
#include "Util.h"

bool Board::move(const char direction)
{
	Vector2D movement;
	const int playerX = m_player->pos.getX();
	const int playerY = m_player->pos.getY();
	if (direction == 'w')
	{
		if (playerY >= 1)
		{
			m_player->move(Vector2D(playerX, playerY - 1));
		}
	}
	else if (direction == 's')
	{
		if (playerY <= m_map.size())
		{
			m_player->move(Vector2D(playerX, playerY + 1));
		}
	}
	else if (direction == 'a')
	{
		if (playerX >= 1)
		{
			m_player->move(Vector2D(playerX - 1, playerY));
		}
	}
	else if (direction == 'd')
	{
		if (playerX <= m_map.size())
		{
			m_player->move(Vector2D(playerX + 1, playerY));
		}
	}
	SharedPtr<ITile> nextField = getField(m_player->pos);
	if (nextField->isGoal())
	{
		return true;
	}
	return false;
}

SharedPtr<ITile> Board::getField(Vector2D position)
{
	const size_t mapSize = m_map.size();
	if (position.getX() >= 0 && position.getX() < mapSize && position.getY() >= 0 && position.getY() < mapSize)
	{
		return m_map[position.getY()][position.getX()];
	}
	return nullptr;
}

Board::Board()
{
	m_map = Util::loadBoard("board.txt");
	m_player = UniquePtr<Player>(new Player(SharedPtr<Board>(this), Vector2D(1, 1)));
}

void Board::render()
{
	using namespace std;
	bool running = true;
	while (running)
	{
		system("cls");
		for (int y = 0; y < m_map.size(); y++)
		{
			for (int x = 0; x < m_map[y].size(); x++)
			{
				if (m_player->pos.getX() == x && m_player->pos.getY() == y)
				{
					cout << 'X';
				}
				else
				{
					m_map[y][x]->render(cout);
				}
			}
			cout << endl;
		}
		cout << endl;
		cout << "Move with w, a, s, d (up, left, down, right). Exit with 0!" << endl;
		cout << m_player->pos.getX() << m_player->pos.getY() << endl;
		char state = _getch();
		if (state == '0')
		{
			cout << "You won!" << endl;
			char tmp;
			cin >> tmp;
			running = false;
		}
		else
		{
			if (move(state))
			{
				running = false;
			}
		}
	}
}
