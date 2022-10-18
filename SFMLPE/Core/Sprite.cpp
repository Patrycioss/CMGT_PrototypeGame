#include "Sprite.hpp"
#include "ResourceManager.hpp"
#include "SFML/Graphics.hpp"

namespace SFMLPE
{
  Sprite::Sprite(const Sprite &other)
		  : GameObject(other)
  {
	  texture_ = other.texture_;
  }

  Sprite::Sprite(sf::Texture* texture, const sf::Vector2f &position, const bool &visible)
		  : GameObject(position, visible)
  {
	  texture_ = texture;
	  sprite_ = sf::Sprite(*texture_);
  }

  Sprite::Sprite(sf::Texture* texture, const float &x, const float &y, const bool &visible)
		  : GameObject(x,y,visible)
  {
	  texture_ = texture;
	  sprite_ = sf::Sprite(*texture_);
  }

  Sprite::Sprite(const char *texturePath, const sf::Vector2f &position, const bool &visible)
		  : GameObject(position, visible)
  {
	  texture_ = ResourceManager::LoadTexture(texturePath);
	  sprite_ = sf::Sprite(*texture_);
	  sprite_ = sf::Sprite(*texture_);
  }

  Sprite::Sprite(const char *texturePath, const float &x, const float &y, const bool &visible)
		  : GameObject(x,y,visible)
  {
	  texture_ = ResourceManager::LoadTexture(texturePath);
	  sprite_ = sf::Sprite(*texture_);
  }

  Sprite::~Sprite() = default;

////////////////////////////////////////////////////////////////////////////////////////////

  const sf::Sprite &Sprite::GetSFMLSprite() const {
	  return sprite_;
  }

////////////////////////////////////////////////////////////////////////////////////////////

  void Sprite::Move(const float &x, const float &y) {
	  GameObject::Move(x,y);
	  sprite_.setPosition(position());
  }

  void Sprite::Move(const sf::Vector2f &vector2) {
	  GameObject::Move(vector2);
	  sprite_.setPosition(position());
  }

  void Sprite::SetPosition(const sf::Vector2f &newPosition) {
	  GameObject::SetPosition(newPosition);
	  sprite_.setPosition(newPosition);
  }

  void Sprite::SetPosition(const float &x, const float &y) {
	  GameObject::SetPosition(x, y);
	  sprite_.setPosition(sf::Vector2f{x,y});
  }

  void Sprite::Render(sf::RenderWindow& window) {
	  window.draw(sprite_);
	  GameObject::Render(window);
  }
}

