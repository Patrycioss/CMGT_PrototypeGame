#include "Sprite.hpp"
#include "../Managers/ResourceManager.hpp"
#include "../Game/Game.hpp"

namespace SFMLPE
{
	Sprite::Sprite(const char *texturePath, const Vector2 &position, const bool &visible)
			: texture_(ResourceManager::GetTexture(texturePath))
			, position_(position)
			, sprite_(sf::Sprite(texture_))
			, ID_(Game::AddSprite(*this))
	{
		sprite_.setPosition(position_.x, position_.y);
	}

	Sprite::Sprite(const char *texturePath, const float &x, const float &y, const bool &visible)
			: texture_(ResourceManager::GetTexture(texturePath))
			, position_(Vector2{x,y})
			, sprite_(sf::Sprite(texture_))
			, ID_(Game::AddSprite(*this))
	{
		sprite_.setPosition(position_.x,position_.y);
	}

	Sprite::~Sprite()
	{
		Game::RemoveSprite(ID_);
	}

	const sf::Sprite &Sprite::GetSFMLSprite() const {
		return sprite_;
	}

	void Sprite::MoveX(const float &amount) {
		position_.x += amount;
	}

	void Sprite::MoveY(const float &amount) {
		position_.y += amount;
	}

	void Sprite::Move(const float &x, const float &y) {
		position_.x += x;
		position_.y += y;
	}

	void Sprite::Move(const Vector2 &vector2) {
		position_ += vector2;
	}
}

