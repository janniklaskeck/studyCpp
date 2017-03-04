#pragma once
#include "Message.h"

class RenderMessage
{
public:
	RenderMessage();
	~RenderMessage();
	static Message Create(sf::RenderWindow* Window);

	static const std::string TYPE_NAME;

private:
	static const int MessageID;
};
