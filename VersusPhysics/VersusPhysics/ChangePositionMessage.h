#pragma once
#include "Message.h"

class ChangePositionMessage
{
public:
	ChangePositionMessage();
	~ChangePositionMessage();

	static Message Create(sf::Vector2f Position);

	static const std::string TYPE_NAME;

private:
	int MessageID = MessageManager::GetTypeID(TYPE_NAME);
};

