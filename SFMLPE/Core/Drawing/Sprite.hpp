﻿#pragma once
#include "SFML/Graphics.hpp"
#include "../Rectangle.hpp"
#include "../GameObject.hpp"

namespace SFMLPE
{
  class Sprite : GameObject
  {
  private:
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

	  const sf::Sprite& GetSFMLSprite() const;

	  ~Sprite();
  };
}
