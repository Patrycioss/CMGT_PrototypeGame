#pragma once


#include "../Core/GameObject.hpp"

namespace SFP {

  class TextObject : public SFP::GameObject
  {
  private:
	  sf::Text text_;
	  std::string fontPath_;

  public:
	  explicit TextObject(const sf::Vector2f& position, const std::string& text="", const std::string& fontPath = "fonts/minecraftFont.ttf",
	             const unsigned int& characterSize = 50);

	  sf::Text& text();
	  sf::RectangleShape& rectShape();

	  void SetFont(const std::string& fontPath);
	  void SetCharacterSize(const unsigned int& size);
	  void SetStyle(const sf::Text::Style& style);
	  void SetPosition(const sf::Vector2f& position) override;
	  
	  
	  void Render(sf::RenderWindow& window) override;
  };
}
