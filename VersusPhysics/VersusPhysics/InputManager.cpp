#include "InputManager.h"

std::map<sf::Keyboard::Key, std::vector<KeyCallback>> InputManager::KeyCallbacks;

bool InputManager::HandleDownEvent(const sf::Event& event)
{
	auto Element = KeyCallbacks.find(event.key.code);
	if (Element != KeyCallbacks.end())
	{
		std::vector<KeyCallback> Callbacks = (*Element).second;
		for (KeyCallback Callback : Callbacks)
		{
			Callback(true);
		}
		return true;
	}
	return false;
}

bool InputManager::HandleUpEvent(const sf::Event & event)
{
	auto Element = KeyCallbacks.find(event.key.code);
	if (Element != KeyCallbacks.end())
	{
		std::vector<KeyCallback> Callbacks = (*Element).second;
		for (KeyCallback Callback : Callbacks)
		{
			Callback(false);
		}
		return true;
	}
	return false;
}

void InputManager::AddKeyCallback(sf::Keyboard::Key Keycode, KeyCallback Callback)
{
	auto Element = KeyCallbacks.find(Keycode);
	if (Element != KeyCallbacks.end())
	{
		std::vector<KeyCallback> Callbacks = (*Element).second;
	}
	else
	{
		std::vector<KeyCallback> Callbacks;
		Callbacks.push_back(Callback);
		KeyCallbacks[Keycode] = Callbacks;
	}
}

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}
