#pragma once
#include "Component.h"
#include "PhysicsComponent.h"
#include "InputState.hpp"
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

	InputState State;

	virtual void ProcessMessage(Message Msg);

	virtual void Update();

private:

	sf::Keyboard::Key UpKey;
	sf::Keyboard::Key DownKey;
	sf::Keyboard::Key RightKey;
	sf::Keyboard::Key LeftKey;
	sf::Keyboard::Key JumpKey;
};
