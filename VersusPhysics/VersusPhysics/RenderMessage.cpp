#include "RenderMessage.hpp"

const std::string RenderMessage::TYPE_NAME = "DO_RENDER_MESSAGE";
const int RenderMessage::MessageID = MessageManager::GetTypeID(RenderMessage::TYPE_NAME);

RenderMessage::RenderMessage()
{
}

RenderMessage::~RenderMessage()
{
}

Message RenderMessage::Create(sf::RenderWindow* Window)
{
	Message Msg;
	Msg.TypeID = MessageType::DO_RENDER;
	Msg.WindowPtrPayload = Window;
	return Msg;
}
