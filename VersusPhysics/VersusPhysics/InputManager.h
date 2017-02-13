#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <functional>
#include <vector>

typedef std::function<void(bool)> KeyCallback;

class InputManager
{
public:

	static bool HandleDownEvent(const sf::Event& event);
	static bool HandleUpEvent(const sf::Event& event);
	
	static void AddKeyCallback(sf::Keyboard::Key Keycode, KeyCallback Callback);

	InputManager();
	~InputManager();

private:
	static std::map<sf::Keyboard::Key, std::vector<KeyCallback>> KeyCallbacks;
};

