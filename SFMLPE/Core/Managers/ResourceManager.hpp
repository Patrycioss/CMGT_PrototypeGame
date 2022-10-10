#pragma once
#include <map>
#include "SFML/Graphics.hpp"

class ResourceManager
{
private:
	static std::map<const char*, sf::Texture> textures;

public:
	static sf::Texture& GetTexture(const char* path);
};
