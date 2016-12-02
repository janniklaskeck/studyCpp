#include "stdafx.h"
#include "Board.h"
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <sstream>

std::string Board::getTopRow()
{
	const int playerX = m_playerPos.getX();
	const int playerY = m_playerPos.getY();
	int topLeft = 8;
	int top = 8;
	int topRight = 8;
	if (playerY >= 1)
	{
		if (playerX >= 1)
		{
			topLeft = m_map[playerX - 1][playerY - 1];
		}
		if (playerX <= 5)
		{
			topRight = m_map[playerX + 1][playerY - 1];
		}
		top = m_map[playerX][playerY - 1];
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
	int bottomLeft = 8;
	int bottom = 8;
	int bottomRight = 8;
	if (playerY <= 5)
	{
		if (playerX >= 1)
		{
			bottomLeft = m_map[playerX - 1][playerY + 1];
		}
		if (playerX <= 5)
		{
			bottomRight = m_map[playerX + 1][playerY + 1];
		}
		bottom = m_map[playerX][playerY + 1];
	}
	std::stringstream ss;
	ss << bottomLeft << bottom << bottomRight;
	return ss.str();
}

std::string Board::getCurrentRow()
{
	const int playerX = m_playerPos.getX();
	const int playerY = m_playerPos.getY();
	int left = 8;
	if (playerX >= 1)
	{
		left = m_map[playerX - 1][playerY];
	}
	int right = 8;
	if (playerX <= 5)
	{
		right = m_map[playerX + 1][playerY];
	}
	int player = 5;
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
		if (playerY >= 1 && m_map[playerX][playerY - 1] != 1)
		{
			movement.setY(-1);
		}
	}
	else if (direction == 's')
	{
		if (playerY <= 5 && m_map[playerX][playerY + 1] != 1)
		{
			movement.setY(1);
		}
	}
	else if (direction == 'a')
	{
		if (playerX >= 1 && m_map[playerX - 1][playerY] != 1)
		{
			movement.setX(-1);
		}
	}
	else if (direction == 'd')
	{
		if (playerX <= 5 && m_map[playerX + 1][playerY] != 1)
		{
			movement.setX(1);
		}
	}
	const Vector2D postMove = Vector2D(playerX + movement.getX(), playerY + movement.getY());
	const int nextField = getField(postMove);
	if (nextField == 2)
	{
		return true;
	}
	else if (nextField != 8)
	{
		m_playerPos += movement;
	}
	return false;
}

int Board::getField(Vector2D position)
{
	const size_t mapSize = m_map.size();
	if (position.getX() >= 0 && position.getX() < mapSize && position.getY() >= 0 && position.getY() < mapSize)
	{
		return m_map[position.getX()][position.getY()];
	}
	return 8;
}

Board::Board()
{
	m_map = std::vector<std::vector<int>>{
		{ 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 1 },
		{ 1, 0, 1, 1, 0, 1 },
		{ 1, 0, 0, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 2 },
		{ 1, 1, 1, 1, 1, 1 },
	};
}


Board::~Board()
{
}

void Board::render()
{
	using namespace std;
	bool running = true;
	while (running)
	{
		system("cls");
		cout << getTopRow() << endl;
		cout << getCurrentRow() << endl;
		cout << getBottomRow() << endl;
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
