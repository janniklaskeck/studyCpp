#pragma once

#include "Message.h"
#include "InputState.hpp"

class InputChangeMessage
{
public:
	InputChangeMessage();
	~InputChangeMessage();

	static Message Create(InputState State);

	static const std::string TYPE_NAME;

private:
	static const int MessageID;
};
