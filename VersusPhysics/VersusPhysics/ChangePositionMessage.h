#pragma once
#include "Message.h"

class ChangePositionMessage
{
public:
	ChangePositionMessage();
	~ChangePositionMessage();

	static Message Create(Vector2 Position);

	static const std::string TYPE_NAME;

private:
	static const int MessageID;
};

