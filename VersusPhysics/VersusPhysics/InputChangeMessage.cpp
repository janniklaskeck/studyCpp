#include "InputChangeMessage.hpp"

const std::string InputChangeMessage::TYPE_NAME = "INPUT_CHANGE_MESSAGE";
const int InputChangeMessage::MessageID = MessageManager::GetTypeID(InputChangeMessage::TYPE_NAME);

InputChangeMessage::InputChangeMessage()
{
}

InputChangeMessage::~InputChangeMessage()
{
}

Message InputChangeMessage::Create(InputState State)
{
	Message Msg;
	Msg.TypeID = MessageType::INPUT_CHANGE;
	Msg.InputPayload = State;
	return Msg;
}
