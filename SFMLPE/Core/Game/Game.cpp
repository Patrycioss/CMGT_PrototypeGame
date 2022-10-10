#include <filesystem>
#include <SFML/Graphics.hpp>

#include "../EventSystem/EventManager.hpp"

namespace SFMLPE
{
	unsigned int Game::lastSpriteID_;
	std::map<const unsigned int, const Sprite&> Game::sprites_;

	WindowSize Game::Size()
	{
		return size_;
	}

	void Game::Run(const int &windowWidth, const int &windowHeight, const char *windowName, const char *resourcePath)
	{
		size_.SetDimensions(windowWidth,windowHeight);
		//Set resource path
		std::string newPath = resourcePath;
		std::filesystem::current_path("../" + newPath);

		Create(windowName);
	}

	void Game::Create(const char *windowName)
	{
		sf::RenderWindow window(sf::VideoMode((unsigned int) size_.width, (unsigned int) size_.height), windowName);

		window.setFramerateLimit(60);

		DoStart();

		while (window.isOpen())
		{
			sf::Event event; // NOLINT(cppcoreguidelines-pro-type-member-init)

			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();

				EventManager::TriggerEvent(event);
			}

			window.clear(sf::Color::Black);

			Update();

			for (std::pair<const unsigned int, const Sprite &> pair : sprites_)
			{
				window.draw(pair.second.GetSFMLSprite());
			}

			window.display();
		}
	}

	unsigned int Game::AddSprite(const Sprite& sprite)
	{
		lastSpriteID_++;
		sprites_.emplace(lastSpriteID_, sprite);
		return lastSpriteID_;
	}

	unsigned int Game::GetSpriteIndex(const unsigned int &spriteID)
	{
		if (!sprites_.contains(spriteID))  {
			printf("Failed to find sprite with ID %d! \n", spriteID);
			return 0;
		}
		else return std::distance(sprites_.begin(), sprites_.find(spriteID));
	}

	void Game::RemoveSprite(const unsigned int& spriteID) {
		if (!sprites_.contains(spriteID)) printf("Couldn't remove sprite with ID %d! \n", spriteID);
		else sprites_.erase(spriteID);
	}
}

