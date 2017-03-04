#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

struct Message
{
	int TypeID = 0;
	union
	{
		sf::Vector2f VectorPayload;
	};
	Message() {};
	~Message() {};
};

class MessageManager
{
public:

	static const int GetTypeID(std::string MessageType);

private:
	static std::vector<std::string> TypeIDs;

	static const int IndexOf(std::string MessageType);
};
