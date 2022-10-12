#include "ResourceManager.hpp"

namespace SFMLPE {

 std::map<const char *, sf::Texture> ResourceManager::textures;

//Loads a texture if the ResourceManager doesn't store it yet.
//Returns a pointer to the stored texture.
 sf::Texture *ResourceManager::LoadTexture(const char *texturePath) {
	 if (textures.contains(texturePath))
		 return &textures[texturePath];

	 sf::Texture texture;

	 if (!texture.loadFromFile(texturePath))
		 return nullptr;

	 return &textures.emplace(texturePath, texture).first->second;
 }


 bool ResourceManager::hasTexture(const char *) {
	 return false;
 }

}