#include "Util.h"
#include <fstream>
#include <iostream>
#include <string>

std::vector<std::vector<char>> Util::loadBoard(char* fileName)
{
	std::ifstream stream(fileName, std::ios::in);

	std::vector<std::vector<char>> board;

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
			board[lineNumber][i] = line[i];
		}
		lineNumber++;
	}

	stream.close();
	return board;
}
