#pragma once
#include "SFML/Graphics.hpp"
#include <map>

namespace SFMLPE {
 class ResourceManager 
 {
 private:
	 static std::map<const char* , sf::Texture> textures;

 public:
	 static sf::Texture* LoadTexture(const char* texturePath);
	 static bool hasTexture(const char* );
 };
}
