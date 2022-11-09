#include "TextInput.hpp"
#include "../Engine/ResourceManager.hpp"


sf::RectangleShape& TextInput::rectShape() {
	return rectShape_;
}

sf::Text& TextInput::text() {
	return text_;
}

void TextInput::Start() {

	eventHandler.Subscribe(sf::Event::TextEntered, [this](const sf::Event& event)
	{
		std::string string = text_.getString();

		if (event.text.unicode == '\b')
		{
			if (string.empty()) return; 
			string.erase(string.size() - 1, 1);
		}
		else if (string.size() != characterLimit)
			string.push_back((char) event.text.unicode);
		else maxCharactersAction_();
		
		
		text_.setString(string);
	});
	
	GameObject::Start();
}

TextInput::TextInput(const sf::Vector2f& position, const sf::Vector2f& size) 
	: GameObject(position)
{
	rectShape_.setPosition(position);
	rectShape_.setSize(size);
	rectShape_.setOutlineThickness(5);
	rectShape_.setOutlineColor(sf::Color::Black);
	text_.setPosition(position.x, position.y);
	text_.setFont(*ResourceManager::LoadFont(fontPath_));
	text_.setCharacterSize(50);
	text_.setFillColor(sf::Color::Black);
}

void TextInput::Render(sf::RenderWindow& window) {
	
	window.draw(rectShape_);
	window.draw(text_);
	
	GameObject::Render(window);
}

void TextInput::SetMaxCharactersAction(const std::function<void()>& action) {
	maxCharactersAction_ = action;
}
