#include "InputComponent.h"
#include "InputChangeMessage.hpp"

InputComponent::InputComponent(sf::Keyboard::Key UpKey,
							   sf::Keyboard::Key DownKey,
							   sf::Keyboard::Key RightKey,
							   sf::Keyboard::Key LeftKey,
							   sf::Keyboard::Key JumpKey) :
	UpKey(UpKey),
	DownKey(DownKey),
	RightKey(RightKey),
	LeftKey(LeftKey),
	JumpKey(JumpKey)
{
	KeyCallback MoveUpIsPressed = [&](bool IsPressed)
	{
		State.MoveUp = IsPressed;
	};
	KeyCallback MoveDownIsPressed = [&](bool IsPressed)
	{
		State.MoveDown = IsPressed;
	};
	KeyCallback MoveRightIsPressed = [&](bool IsPressed)
	{
		State.MoveRight = IsPressed;
	};
	KeyCallback MoveLeftIsPressed = [&](bool IsPressed)
	{
		State.MoveLeft = IsPressed;
	};
	KeyCallback MoveJumpIsPressed = [&](bool IsPressed)
	{
		State.MoveJump = IsPressed;
	};
	InputManager::AddKeyCallback(UpKey, MoveUpIsPressed);
	InputManager::AddKeyCallback(DownKey, MoveDownIsPressed);
	InputManager::AddKeyCallback(RightKey, MoveRightIsPressed);
	InputManager::AddKeyCallback(LeftKey, MoveLeftIsPressed);
	InputManager::AddKeyCallback(JumpKey, MoveJumpIsPressed);
}

void InputComponent::ProcessMessage(Message Msg)
{

}

void InputComponent::Update()
{
	Parent->Broadcast(InputChangeMessage::Create(State));
}
