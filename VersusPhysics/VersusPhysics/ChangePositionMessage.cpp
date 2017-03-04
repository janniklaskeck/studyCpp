#include "ChangePositionMessage.h"

const std::string ChangePositionMessage::TYPE_NAME = "CHANGE_POSITION_MESSAGE";
const int ChangePositionMessage::MessageID = MessageManager::GetTypeID(ChangePositionMessage::TYPE_NAME);

ChangePositionMessage::ChangePositionMessage()
{
}

ChangePositionMessage::~ChangePositionMessage()
{
}

Message ChangePositionMessage::Create(sf::Vector2f Position)
{
	Message Msg;
	Msg.TypeID = MessageType::POSITION_CHANGE;
	Msg.VectorPayload = Position;
	return Msg;
}
