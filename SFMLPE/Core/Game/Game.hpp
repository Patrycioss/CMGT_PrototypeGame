#pragma once

#include <map>
#include <SFML/Graphics.hpp>

#include "WindowSize.hpp"
#include "../Drawing/Sprite.hpp"

namespace SFMLPE
{
	class Game{
	private:
		static unsigned int lastSpriteID_;
		static std::map<const unsigned int, const Sprite&> sprites_;

		void Create(const char* windowName);
		void DoStart() {Start();};
		void DoUpdate() {Update();};
		Rectangle rect_;

	protected:
		virtual void Start(){};
		virtual void Update(){};

	public:
		void Run(const int& windowWidth, const int& windowHeight, const char* windowName = "My Game", const char* resourcePath = "");
		sf::Vector2f Size() const;




		static unsigned int AddSprite(const Sprite& sprite);
		static void RemoveSprite(const unsigned int& spriteID);
		static unsigned int GetSpriteIndex(const unsigned int& spriteID);
	};

}
