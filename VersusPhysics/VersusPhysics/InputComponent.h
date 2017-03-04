#pragma once
#include "Component.h"
#include "PhysicsComponent.h"
#include "InputManager.h"
#include "Constants.h"
#include "Message.h"
class InputComponent : public Component
{
public:

	InputComponent(sf::Keyboard::Key UpKey,
				   sf::Keyboard::Key DownKey,
				   sf::Keyboard::Key RightKey,
				   sf::Keyboard::Key LeftKey,
				   sf::Keyboard::Key JumpKey);

	bool MoveUp = false;
	bool MoveDown = false;
	bool MoveRight = false;
	bool MoveLeft = false;
	bool MoveJump = false;

	void ProcessMessage(Message Msg) {};

private:

	sf::Keyboard::Key UpKey;
	sf::Keyboard::Key DownKey;
	sf::Keyboard::Key RightKey;
	sf::Keyboard::Key LeftKey;
	sf::Keyboard::Key JumpKey;
};
