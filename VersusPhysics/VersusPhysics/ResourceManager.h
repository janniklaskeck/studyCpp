#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <map>

class ResourceManager
{
public:

	static std::shared_ptr<sf::Texture> LoadTexture(const std::string& path);

};

