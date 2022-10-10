#include "ResourceManager.hpp"

std::map<const char*, sf::Texture> ResourceManager::textures;

sf::Texture& ResourceManager::GetTexture(const char* path) {

	if (!textures.empty() && textures.contains(path)) {
		printf("Jawel");
		return textures[path];
	}
	sf::Texture texture;

	if (texture.loadFromFile(path)) textures[path] = texture;

	return textures[path];
}