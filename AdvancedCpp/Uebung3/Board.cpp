#include "stdafx.h"
#include "Board.h"
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <sstream>
#include "Util.h"

std::string Board::getTopRow()
{
	const int playerX = m_playerPos.getX();
	const int playerY = m_playerPos.getY();
	char topLeft = 'X';
	char top = 'X';
	char topRight = 'X';
	if (playerY >= 1)
	{
		if (playerX >= 1)
		{
			topLeft = m_map[playerX - 1][playerY - 1]->displayChar;
		}
		if (playerX <= 5)
		{
			topRight = m_map[playerX + 1][playerY - 1]->displayChar;
		}
		top = m_map[playerX][playerY - 1]->displayChar;
	}
	std::string row;
	std::stringstream ss;
	ss << topLeft << top << topRight;
	return ss.str();
}

std::string Board::getBottomRow()
{
	const int playerX = m_playerPos.getX();
	const int playerY = m_playerPos.getY();
	char bottomLeft = 'X';
	char bottom = 'X';
	char bottomRight = 'X';
	if (playerY <= 5)
	{
		if (playerX >= 1)
		{
			bottomLeft = m_map[playerX - 1][playerY + 1]->displayChar;
		}
		if (playerX <= 5)
		{
			bottomRight = m_map[playerX + 1][playerY + 1]->displayChar;
		}
		bottom = m_map[playerX][playerY + 1]->displayChar;
	}
	std::stringstream ss;
	ss << bottomLeft << bottom << bottomRight;
	return ss.str();
}

std::string Board::getCurrentRow()
{
	const int playerX = m_playerPos.getX();
	const int playerY = m_playerPos.getY();
	char left = 'X';
	if (playerX >= 1)
	{
		left = m_map[playerX - 1][playerY]->displayChar;
	}
	char right = 'X';
	if (playerX <= 5)
	{
		right = m_map[playerX + 1][playerY]->displayChar;
	}
	char player = 'O';
	std::stringstream ss;
	ss << left << player << right;
	return ss.str();
}

bool Board::move(const char direction)
{
	Vector2D movement;
	const int playerX = m_playerPos.getX();
	const int playerY = m_playerPos.getY();
	if (direction == 'w')
	{
		if (playerY >= 1 && !m_map[playerX][playerY - 1]->isBlocking())
		{
			movement.setY(-1);
		}
	}
	else if (direction == 's')
	{
		if (playerY <= m_map.size() && !m_map[playerX][playerY + 1]->isBlocking())
		{
			movement.setY(1);
		}
	}
	else if (direction == 'a')
	{
		if (playerX >= 1 && !m_map[playerX - 1][playerY]->isBlocking())
		{
			movement.setX(-1);
		}
	}
	else if (direction == 'd')
	{
		if (playerX <= m_map.size() && !m_map[playerX + 1][playerY]->isBlocking())
		{
			movement.setX(1);
		}
	}
	const Vector2D postMove = Vector2D(playerX + movement.getX(), playerY + movement.getY());
	ITile* nextField = getField(postMove);
	if (nextField->isGoal())
	{
		return true;
	}
	else if (!nextField->isBlocking())
	{
		m_playerPos += movement;
	}
	return false;
}

ITile* Board::getField(Vector2D position)
{
	const size_t mapSize = m_map.size();
	if (position.getX() >= 0 && position.getX() < mapSize && position.getY() >= 0 && position.getY() < mapSize)
	{
		return m_map[position.getX()][position.getY()];
	}
	return new Wall;
}

Board::Board()
{
	m_map = Util::loadBoard("board.txt");
}

Board::~Board()
{
	for (int x = 0; x < m_map.size(); x++)
	{
		for (int y = 0; y < m_map[x].size(); y++)
		{
			delete m_map[x][y];
		}
	}
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
				if (m_playerPos.getX() == x && m_playerPos.getY() == y)
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
		cout << m_playerPos.getX() << m_playerPos.getY() << endl;
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
