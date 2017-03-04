#pragma once

#include "InputState.hpp"

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

enum MessageType
{
	NOTHING,
	INPUT_CHANGE,
	POSITION_CHANGE,
	DO_RENDER
};

struct Message
{
	MessageType TypeID = NOTHING;
	union
	{
		sf::RenderWindow* WindowPtrPayload;
		InputState InputPayload;
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
