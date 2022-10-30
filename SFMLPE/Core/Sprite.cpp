#include "Sprite.hpp"
#include "ResourceManager.hpp"
#include "SFML/Graphics.hpp"

namespace SFMLPE
{
  Sprite::Sprite() : GameObject(0,0, false)
  {}

  Sprite::Sprite(sf::Texture* texture, const sf::Vector2f &position, const bool &visible)
		  : GameObject(position, visible)
  {
	  texture_ = texture;
	  sprite_ = sf::Sprite(*texture_);
	  sprite_.setPosition(position);
	  UpdateSize();
  }

  Sprite::Sprite(sf::Texture* texture, const float &x, const float &y, const bool &visible)
		  : GameObject(x,y,visible)
  {
	  texture_ = texture;
	  sprite_ = sf::Sprite(*texture_);
	  sprite_.setPosition(sf::Vector2f{x,y});
	  UpdateSize();
  }

  Sprite::Sprite(const char *texturePath, const sf::Vector2f &position, const bool &visible)
		  : GameObject(position, visible)
  {
	  texture_ = ResourceManager::LoadTexture(texturePath);
	  sprite_ = sf::Sprite(*texture_);
	  sprite_.setPosition(position);
	  UpdateSize();
  }

  Sprite::Sprite(const char *texturePath, const float &x, const float &y, const bool &visible)
		  : GameObject(x,y,visible)
  {
	  texture_ = ResourceManager::LoadTexture(texturePath);
	  sprite_ = sf::Sprite(*texture_);
	  sprite_.setPosition(sf::Vector2f{x,y});
	  UpdateSize();
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
  

  void Sprite::MirrorVert(const bool& mirror) {	  
	  GameObject::MirrorVert(mirror);
	  sf::Vector2f scale = sprite_.getScale();
	  
	  if (mirror)
	  {
		  if (scale.x > 0) 
			  scale.x = -scale.x;
	  }
	  else if (scale.x < 0) 
		  scale.x = -scale.x;
	  
	  sprite_.setScale(scale);
  }

  void Sprite::MirrorHor(const bool& mirror){
	  GameObject::MirrorHor(mirror);
	  
	  sf::Vector2f scale = sprite_.getScale();

	  if (mirror)
	  {
		  if (scale.y > 0)
			  scale.y = -scale.y;
	  }
	  else if (scale.y < 0)
		  scale.y = -scale.y;

	  sprite_.setScale(scale);
  }

  void Sprite::SetOnlyThisPosition(const sf::Vector2f& newPosition) {
	  GameObject::SetOnlyThisPosition(newPosition);
	  sprite_.setPosition(newPosition);
  }

  void Sprite::SetOnlyThisPosition(const float& x, const float& y) {
	  GameObject::SetOnlyThisPosition(x, y);
	  sprite_.setPosition(sf::Vector2f{x,y});
  }
  
  void Sprite::UpdateSize() 
  {
	  GameObject::UpdateSize( 
			    (float) texture_->getSize().x
			  , (float) texture_->getSize().y);
  }

  void Sprite::UpdateScale(const sf::Vector2f& prevScale) 
  {
	  GameObject::UpdateScale(prevScale);
	  
	  sf::Vector2f scale = this->scale();
	  if (horMirrored()) scale.y *= -1;
	  if (vertMirrored()) scale.x *= -1;
	  
	  sprite_.setScale(scale);
  }

}

