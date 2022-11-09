#pragma once


#include "../Engine/GameObject.hpp"

class TextInput: public GameObject
{
private:
	
	sf::RectangleShape rectShape_;
	
	sf::Text text_;
	const char* fontPath_ = "fonts/minecraftFont.ttf";
	
	std::function<void()> maxCharactersAction_;
	
public:
	TextInput(const sf::Vector2f& position, const sf::Vector2f& size);
	
	unsigned int characterLimit = 20;
	sf::RectangleShape& rectShape();
	sf::Text& text();
	
	void Start() override;
	void Render(sf::RenderWindow&) override;
	
	void SetMaxCharactersAction(const std::function<void()>& action);
};
