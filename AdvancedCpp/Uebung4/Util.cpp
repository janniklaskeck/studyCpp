#include "Util.h"
#include <fstream>
#include <iostream>
#include <string>

#include "Wall.h"
#include "Freespace.h"
#include "Goal.h"

std::vector<std::vector<SharedPtr<ITile>>> Util::loadBoard(char* fileName)
{
	std::ifstream stream(fileName, std::ios::in);

	std::vector<std::vector<SharedPtr<ITile>>> board;

	size_t boardSize = 0;
	int lineNumber = 0;
	std::string line;
	while (getline(stream, line))
	{
		if (boardSize == 0)
		{
			boardSize = line.length();
			board.resize(10);
		}
		for (int i = 0; i < boardSize; i++)
		{
			board[lineNumber].resize(10);
			if (line[i] == 'W')
			{
				board[lineNumber][i] = SharedPtr<ITile>(new Wall(Vector2D(i, lineNumber)));
			}
			else if (line[i] == 'G')
			{
				board[lineNumber][i] = SharedPtr<ITile>(new Goal(Vector2D(i, lineNumber)));

			}
			else
			{
				board[lineNumber][i] = SharedPtr<ITile>(new Freespace(Vector2D(i, lineNumber)));
			}

		}
		lineNumber++;
	}

	stream.close();
	return board;
}
