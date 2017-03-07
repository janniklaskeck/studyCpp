#pragma once

#include "InputState.hpp"
#include "Vector2.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
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
		Vector2 VectorPayload;
	};

	Message()
	{
	}
	Message(const Message& Other)
	{
		if (this != &Other)
		{
			this->TypeID = Other.TypeID;
			this->WindowPtrPayload = Other.WindowPtrPayload;
			this->InputPayload = Other.InputPayload;
			this->VectorPayload = Other.VectorPayload;
		}
	}
	~Message()
	{
	}

	Message& operator=(const Message& Other)
	{
		if (this != &Other)
		{
			this->TypeID = Other.TypeID;
			this->WindowPtrPayload = Other.WindowPtrPayload;
			this->InputPayload = Other.InputPayload;
			this->VectorPayload = Other.VectorPayload;
		}
		return *this;
	}
};

class MessageManager
{
public:

	static const int GetTypeID(std::string MessageType);

private:
	static std::vector<std::string> TypeIDs;

	static const int IndexOf(std::string MessageType);
};
