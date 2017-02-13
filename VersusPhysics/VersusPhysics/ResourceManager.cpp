#include "ResourceManager.h"
#include <stdio.h>

std::shared_ptr<sf::Texture> ResourceManager::LoadTexture(const std::string& path)
{
	std::shared_ptr<sf::Texture> LoadedTexture = std::make_shared<sf::Texture>();
	LoadedTexture->setSmooth(true);
	if (!LoadedTexture->loadFromFile(path))
	{
		printf("Could not load Image! %s\n", path.c_str());
	}
	return LoadedTexture;
}


