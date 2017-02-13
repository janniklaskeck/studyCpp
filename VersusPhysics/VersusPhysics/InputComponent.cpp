#include "InputComponent.h"

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
		MoveUp = IsPressed;
	};
	KeyCallback MoveDownIsPressed = [&](bool IsPressed)
	{
		MoveDown = IsPressed;
	};
	KeyCallback MoveRightIsPressed = [&](bool IsPressed)
	{
		MoveRight = IsPressed;
	};
	KeyCallback MoveLeftIsPressed = [&](bool IsPressed)
	{
		MoveLeft = IsPressed;
	};
	KeyCallback MoveJumpIsPressed = [&](bool IsPressed)
	{
		MoveJump = IsPressed;
	};
	InputManager::AddKeyCallback(UpKey, MoveUpIsPressed);
	InputManager::AddKeyCallback(DownKey, MoveDownIsPressed);
	InputManager::AddKeyCallback(RightKey, MoveRightIsPressed);
	InputManager::AddKeyCallback(LeftKey, MoveLeftIsPressed);
	InputManager::AddKeyCallback(JumpKey, MoveJumpIsPressed);
}
