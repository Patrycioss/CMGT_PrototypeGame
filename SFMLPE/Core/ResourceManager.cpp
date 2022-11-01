#include "ResourceManager.hpp"

namespace SFP {

 std::unordered_map<std::string, std::pair<sf::Texture, unsigned int>> ResourceManager::textures_;
 std::unordered_map<std::string, std::pair<sf::Font, unsigned int>> ResourceManager::fonts_;
 std::unordered_map<std::string, std::pair<sf::SoundBuffer, unsigned int>> ResourceManager::soundBuffers_;

//Loads a texture if the ResourceManager doesn't store it yet.
//Returns a pointer to the stored texture.
 sf::Texture* ResourceManager::LoadTexture(const std::string& texturePath) {
	  if (textures_.contains(texturePath)) {
		  textures_[texturePath].second++;
		  return &textures_[texturePath].first;
	  }

	  sf::Texture texture;

	  if (!texture.loadFromFile(texturePath)) {
		  printf("Failed to load texture with path %s \n", texturePath.c_str());
		  return nullptr;
	  }

	  printf("Loaded texture with path %s \n", texturePath.c_str());

	  textures_[texturePath] = std::pair(texture, 1);

	  return &textures_[texturePath].first;
 }


 bool ResourceManager::hasTexture(const std::string& texturePath) {
	 return textures_.contains(texturePath);
 }

  sf::Texture* ResourceManager::texture(const std::string& texturePath) {
	 if (textures_.contains(texturePath)) return &textures_[texturePath].first;
	 else return nullptr;
  }

  bool ResourceManager::RemoveTexture(const std::string& texturePath) {
	  if (textures_.contains(texturePath))
	  {
		  unsigned int& count = textures_[texturePath].second;
		  count--;
		  
		  if (count == 0)
		  {
			  textures_.erase(texturePath);
		  }
		  return true;
	  }
	  else return false;
  }

  sf::Font* ResourceManager::LoadFont(const std::string& fontPath) {
	  if (fonts_.contains(fontPath)) {
		  fonts_[fontPath].second++;
		  return &fonts_[fontPath].first;
	  }

	  sf::Font font;

	  if (!font.loadFromFile(fontPath)) {
		  printf("Failed to load font with path %s \n", fontPath.c_str());
		  return nullptr;
	  }

	  printf("Loaded font with path %s \n", fontPath.c_str());
	  
	  return &fonts_.insert(std::pair(fontPath, std::pair(font,1))).first->second.first;
  }

  bool ResourceManager::RemoveFont(const std::string& fontPath) {
	  if (fonts_.contains(fontPath))
	  {
		  unsigned int& count = fonts_[fontPath].second;
		  count--;

		  if (count == 0)
		  {
			  fonts_.erase(fontPath);
		  }
		  return true;
	  }
	  else return false;  
 }

  sf::Font* ResourceManager::font(const std::string& fontPath) {
	  if (fonts_.contains(fontPath)) return &fonts_[fontPath].first;
	  else return nullptr;
  }

  bool ResourceManager::hasFont(const std::string& fontPath) {		 
	 return fonts_.contains(fontPath);
  }

  sf::SoundBuffer* ResourceManager::LoadSoundBuffer(const std::string& soundFilePath) {
	  if (soundBuffers_.contains(soundFilePath)) {
		  soundBuffers_[soundFilePath].second++;
		  return &soundBuffers_[soundFilePath].first;
	  }

	  sf::SoundBuffer soundBuffer;

	  if (!soundBuffer.loadFromFile(soundFilePath)) {
		  printf("Failed to load soundBuffer with path %s \n", soundFilePath.c_str());
		  return nullptr;
	  }

	  printf("Loaded soundBuffer with path %s \n", soundFilePath.c_str());
	  
	  return &soundBuffers_.insert(std::pair(soundFilePath, std::pair(soundBuffer, 1))).first->second.first;
  }

  bool ResourceManager::RemoveSoundBuffer(const std::string& soundFilePath) {
	  if (soundBuffers_.contains(soundFilePath))
	  {
		  unsigned int& count = soundBuffers_[soundFilePath].second;
		  count--;

		  if (count == 0)
		  {
			  soundBuffers_.erase(soundFilePath);
		  }
		  return true;
	  }
	  else return false;
  }

  sf::SoundBuffer* ResourceManager::soundBuffer(const std::string& soundFilePath) {
	  if (soundBuffers_.contains(soundFilePath)) return &soundBuffers_[soundFilePath].first;
	  else return nullptr;
  }

  bool ResourceManager::hasSoundBuffer(const std::string& soundFilePath) {
	  return soundBuffers_.contains(soundFilePath);
  }
}