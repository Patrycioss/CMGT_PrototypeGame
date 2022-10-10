#pragma once
#include "SFML/Graphics.hpp"
#include "../Vector2.hpp"

namespace SFMLPE
{
	class Sprite
	{
	private:
		Vector2 position_;
		unsigned int ID_;
		sf::Texture& texture_;
		sf::Sprite sprite_;

	public:
		Sprite(const char* texturePath, const Vector2& position, const bool& visible = true);
		Sprite(const char* texturePath, const float& x, const float& y, const bool& visible = true);

		
		void MoveX(const float& amount);
		void MoveY(const float& amount);
		void Move(const float& x, const float& y);
		void Move(const Vector2& vector2);
		
		const sf::Sprite& GetSFMLSprite() const;

		~Sprite();

	};
}
