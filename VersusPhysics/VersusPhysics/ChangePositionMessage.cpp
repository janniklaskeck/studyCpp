#include "ChangePositionMessage.h"

const std::string ChangePositionMessage::TYPE_NAME = "CHANGE_POSITION_MANAGE";

ChangePositionMessage::ChangePositionMessage()
{
}

ChangePositionMessage::~ChangePositionMessage()
{
}

Message ChangePositionMessage::Create(sf::Vector2f Position)
{
	Message Msg;
	Msg.VectorPayload = Position;
	return Msg;
}
