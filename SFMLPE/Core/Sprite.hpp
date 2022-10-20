#pragma once
#include "SFML/Graphics.hpp"
#include "Rectangle.hpp"
#include "GameObject.hpp"

namespace SFMLPE
{
  class Sprite : public GameObject
  {
  protected:
	  sf::Texture* texture_;
	  sf::Sprite sprite_;

  public:
	  Sprite(const Sprite& other);
	  Sprite(sf::Texture* texture, const sf::Vector2f& position, const bool& visible = true);
	  Sprite(sf::Texture* texture, const float& x, const float& y, const bool& visible = true);
	  Sprite(const char* texturePath, const sf::Vector2f& position, const bool& visible = true);
	  Sprite(const char* texturePath, const float& x, const float& y, const bool& visible = true);

	  void SetPosition(const sf::Vector2f& newPosition) override;
	  void SetPosition(const float& x, const float& y) override;
	  void Move(const float& x, const float& y) override;
	  void Move(const sf::Vector2f& transformation) override;
	  
	  sf::Vector2f size() const override;

	  void MirrorVert(const bool& mirrored, const bool& stemsFromRecursion = false) override;
	  void MirrorHor(const bool& mirrored) override;
	  
	 

	  const sf::Sprite& GetSFMLSprite() const;

	  void Render(sf::RenderWindow& window) override;
	  
	  ~Sprite();
	  
  protected:
	  void SetPositionMirror(const sf::Vector2f &newPosition) override;
	  void SetPositionMirror(const float &x, const float &y) override;
  };
}
