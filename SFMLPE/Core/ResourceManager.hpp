#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <map>

namespace SFP {
 class ResourceManager 
 {
 private:
	 static std::unordered_map<std::string, std::pair<sf::Texture, unsigned int>> textures_;
	 static std::unordered_map<std::string, std::pair<sf::Font, unsigned int>> fonts_;
	 static std::unordered_map<std::string, std::pair<sf::SoundBuffer, unsigned int>> soundBuffers_;

 public:
	 static sf::Texture* LoadTexture(const std::string& texturePath);
	 static bool RemoveTexture(const std::string& texturePath);
	 static sf::Texture* texture(const std::string& texturePath);
	 static bool hasTexture(const std::string& texturePath);


	 static sf::Font* LoadFont(const std::string& fontPath);
	 static bool RemoveFont(const std::string& fontPath);
	 static sf::Font* font(const std::string& fontPath);
	 static bool hasFont(const std::string& fontPath);

	 static sf::SoundBuffer* LoadSoundBuffer(const std::string& soundFilePath);
	 static bool RemoveSoundBuffer(const std::string& audioFilePath);
	 static sf::SoundBuffer* soundBuffer(const std::string& audioFilePath);
	 static bool hasSoundBuffer(const std::string& audioFilePath);
 };
}
