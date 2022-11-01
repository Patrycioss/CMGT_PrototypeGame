#include "TextObject.hpp"
#include "../Core/ResourceManager.hpp"

namespace SFP {

  TextObject::TextObject(const sf::Vector2f& position, const std::string& text, const std::string& fontPath, const unsigned int& characterSize)
		  : SFP::GameObject(position) {
	  text_.setPosition(position);
	  text_.setFont(*ResourceManager::LoadFont(fontPath));
	  text_.setCharacterSize(characterSize);
  }

  sf::Text& TextObject::text() {
	  return text_;
  }

  sf::RectangleShape& TextObject::rectShape() {
	  return rect_;
  }

  void TextObject::Render(sf::RenderWindow& window) {
	  window.draw(text_);
	  window.draw(rect_);
	  GameObject::Render(window);
  }

  void TextObject::SetFont(const std::string& fontPath) {
	  
	  if (!fontPath_.empty()) ResourceManager::RemoveFont(fontPath_);
	  
	  text_.setFont(*ResourceManager::LoadFont(fontPath));
	  fontPath_ = fontPath;
  }

  void TextObject::SetCharacterSize(const unsigned int& size) {
	  text_.setCharacterSize(size);
  }

  void TextObject::SetStyle(const sf::Text::Style& style) {
	  text_.setStyle(style);
  }

  void TextObject::SetPosition(const sf::Vector2f& position) {
	  text_.setPosition(position);
	  GameObject::SetPosition(position);
  }

};
